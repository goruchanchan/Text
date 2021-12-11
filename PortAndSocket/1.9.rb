#!/usr/bin/ruby

require 'net/http'

result = Net::HTTP.get('www.example.com','/')

p result
