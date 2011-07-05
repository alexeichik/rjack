module RJackExt
  def start_server(reload_alsa = true)
    if reload_alsa
      `sudo /sbin/alsa force-reload`
      sleep(3)
    end
    `jackd -d alsa -r -P -nozombies`
  end
end