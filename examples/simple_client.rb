require "rjack"

module RJack
  extend self
end

puts RJack.methods - Module.methods


TABLE_SIZE = 200
$sine = Array.new(TABLE_SIZE)
$output_port = nil
$phase = 0

#def process(frames_count, data) #process (jack_nframes_t nframes, void *arg)
#  out = RJack.port_get_buffer($output_port, frames_count)
#  (0...frames_count).each do |index|
#    out[index] = $sine[$phase]
#    $phase += 1
#    $phase -= TABLE_SIZE if $phase >= TABLE_SIZE
#  end
#end
#
#def shutdown(arg)
#  puts "shutdown"
#  exit(1)
#end
#
#(0...TABLE_SIZE).each do |index|
#  $sine[index] = 0.2 * Math.sin(2 * Math::PI * index / TABLE_SIZE)
#end

$client, status = RJack.client_open("ported simple client")
unless $client
  puts "RJack.client_open() failed, status = #{status}"
#  puts "Unable to connect to JACK server" if RJack.server_failed?
  exit(1)
end
#
#if status && RJack.name_not_unique?
#  client_name = RJack.client_name($client)
#  puts "unique name '#{client_name}' assigned"
#end
#
#RJack.set_process_callback($client, method(:process))
#
#RJack.on_shutdown($client, mathod(:shutdown))
#
#$output_port = RJack.port_register($client, "simple client output", RJack::DEFAULT_AUDIO_TYPE, RJack::PORTS_OUTPUT, 0)
#raise "no more JACK ports available" unless $output_port
#
#raise "cannot activate client" if RJack.activate($client)
#
#ports = RJack.ports($client, nil, nil, RJack.PORTS_PHYSICAL | RJack.PORTS_OUTPUT)
#raise "no physical playback ports" unless port
#
#raise "cannot connect output port" if RJack.connect($client, RJack.port_name(output_port), ports.first)
#
#RJack.free(ports)
#
#30.times do
#  sleep(1)
#end
#
#RJack.client_close($client)
