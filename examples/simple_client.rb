require "pavel/rjack"

TABLE_SIZE = 200
$sine = Array.new(TABLE_SIZE)
$output_port = nil
$phase = 0

(0...TABLE_SIZE).each do |index|
  $sine[index] = 0.2 * Math.sin(2 * Math::PI * index / TABLE_SIZE)
end

#RJack.start_server
$client, status = RJack.client_open("ported simple client")
unless $client
  puts "RJack.client_open() failed, status = #{status}"
  exit(1)
end

if status.name_not_unique?
  puts "unique name '#{$client.name}' assigned"
end

$client.on_process do |frames_count|
  out = $output_port.get_buffer(frames_count)
  (0...frames_count).each do |index|
    out[index] = $sine[$phase]
    $phase += 1
    $phase -= TABLE_SIZE if $phase >= TABLE_SIZE
  end
end

$client.on_shutdown do
  puts "Client received shutdown"
  exit(1)
end

$output_port = $client.register_port("simple client output")

raise "no more JACK ports available" unless $output_port

raise "cannot activate client" unless $client.activate

ports = $client.ports
raise "no physical playback ports" if ports.empty?

raise "cannot connect output port" unless $client.connect_ports($output_port, ports.first)

#ports.each &:free

puts "before sleep"
sleep(2000)
puts "WAKE UP"

$client.close
