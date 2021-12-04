class Dynamic
  def initialize
    @hash = {}
  end

  attr_reader :hash

  def method_missing(method, price)
    puts "You called #{method} with a price of #{price}"
    @hash[:method] = price
  end

  def respond_to_missing?(_method, _include_private = false)
    true
  end
end

bob = Dynamic.new
bob.send(:computer, price: 500)
p bob.respond_to?(:computer)
p bob.hash
