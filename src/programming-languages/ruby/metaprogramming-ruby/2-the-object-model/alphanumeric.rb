# remove all non alphanumeric characters.
def to_alphanumeric(str)
  str.gsub(/[^w|s]/, '')
end

# This is a generic method that makes sense for all strings.
# Let's add it to the String class.

class String
  def to_alphanumeric(str)
    str.gsub(/[^w|s]/, '')
  end
end

# Let's test

require 'test/unit'

class StringExtensionTest < Test::Unit::TestCase
  def test_strip_non_alphanumeric_characters
    assert_equal '3 the Magic Number', '#3, the *Magic, Number*?'.to_alphanumeric
  end
end
