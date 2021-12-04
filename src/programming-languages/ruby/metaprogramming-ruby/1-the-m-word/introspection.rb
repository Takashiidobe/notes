class Greeting
  def initialize(text)
    @text = text
  end

  def welcome
    @text
  end
end

my_object = Greeting.new('Hello')
puts "This is my object: #{my_object}"

puts "My class is: #{my_object.class}"
puts "My instance_methods are: #{my_object.instance_methods(false)}"
puts "These are my instance variables: #{my_object.instance_variables}"
