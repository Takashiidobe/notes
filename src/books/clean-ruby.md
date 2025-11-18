---
title: clean-ruby
---

# Clean Ruby

## Chapter 1 The qualities of clean code

Clean Code is:

- Readable
- Easy to change
- Straightforward

Is this code readable?

```rb
def method1(t, b)
  c = t + b
  return c
end
```

This could be:

```rb
def sum(a, b)
  a + b
end
```

Extensibility

Instead of:

```rb
def log(message, level)
  if level.to_s == 'warning'
    puts "WARN: #{message}"
  elsif level.to_s == 'info'
    puts "INFO: #{message}"
  elsif level.to_s == 'error'
    puts "ERROR: #{message}"
  end
end

log("Something happened", :info)
```

We could try:

```rb
def log(message, level)
  puts "#{level.to_s.upcase}: #{message}"
end

log("An error occurred", error)
```

Instead of:

```rb
def log_to_console(args)
  if args.length > 1
    if args[1] == 'warn'
      puts 'WARN: ' + args[0]
    elsif args[1] == 'error'
      puts 'ERROR: ' + args[0]
    else
      puts args[0]
    end
  end
end

args = ['A message', 'warn'] log_to_console(args)
```

```rb
def log_to_console(message, level)
  puts "#{level.to_s.upcase}: #{message}"
end

log_to_console('A message', :warn)
```

## Chapter 2 Naming Things

- Names must be properly written out.
- Hungarian notation is not great, since the type is embedded in the
  variable.

Instead of:

```rb
def state_tax(total)
  total * 0.2
end

def federal_tax(total)
  total * 0.1
end
```

```rb
class Tax
  def initialize(total)
  # Total is now an instance variable
  # and can be accessed by all methods
    @total = total
  end
  def state
    @total * 0.2
  end
  def federal
    @total * 0.1
  end
end
```

Prefer snake_case for variables and functions, and Camel case for
Classes.

## Keep data contained.

```rb
# Bad Example
user = 'bob'

# Good example
first_name = 'bob'
```

```rb
# Bad example
start_data = { players: 4, score_to_win: 5 } 3
# Good example
game_config = { players: 4, score_to_win: 5 }
```

### Length

- Keep variable names short.

```rb
# Bad example
purchase_final_sale_total = 300
 # Good example
sale_total = 300
```

Try to avoid generic words like

- Manager
- Data
- Info
- List

that don't convey information to the reader.

Instead of:

```rb
# Bad example
class PlayerManager
  def spawn(player_id)
    @players << Player.new(player_id)
  end
end
player_manager = PlayerManager.new
player_manager.spawn(1)
```

```rb
# Good Example
class PlayerSpawner
  def spawn(player_id)
    @playeds << Player.new(player_id)
  end
end

player_manager = PlayerManager.new
player_manager.spawn(1)
```

Avoid conjunctions, instead use two variables.

Instead of

```rb
score_and_player_count = { score: 100, player_count: 2 }
```

do:

```rb
score = 100
player_count = 2
```

### Only use Alpha Characters for variable namess

```rb
# Bad example
year_1985 = 1985

# Good Example
start_of_grunge = 1985
```

### Methods

#### Use Verbs

- Methods are doers, so have verbs.

```rb
class Account
  def initialize(customer)
    @customer = customer
  end

  # Bad method
  def money(amount)
    @customer.balance -= amount
  end
end
```

```rb
class Account
  def initialize(customer)
    @customer = customer
  end

  # Good method
  def pay_bill(amount)
    @customer.balance -= amount
  end
end
```

### Return Value

- rubyists prefer using a question mark when a function or method
  returns a boolean.

```rb
# bad example
def is_equal(a, b)
  a == b
end

# good example
def equal?(a, b)
  a == b
end
```

- Rubyists use an exclamation mark for mutating methods, that change
  the data they work on.

```rb
class User
attr_accessor :friends
  def remove_friend!(friend)
    @friends.delete(friend)
  end
end
```

### Classes

Classes are the building blocks of ruby code. They should be a Noun that
contains verbs that act on the classs.

The class contains state internally, and the methods operate on said
state. Rather than free standing functions like this:

```rb
def new_user_add_coins
# code
end

def email_new_user_welcome(email)
# send an email
end

user_email = 'example@example.com'
new_user_add_coins
email_new_user_welcome(user_email)
```

```rb
class UserSetup
  def initialize(user)
    @user = user
  end
  def execute
    add_coins
    send_welcome
  end

  private
  def add_coins
    # add coins to their account
  end
  def send_welcome
    email = @user.email # send an email
  end
end

user_setup = UserSetup.new(user)
user_setup.execute
```

#### Role

Some classes offer a particular role.

#### Modules

- A module is a class that you can't instantiate; instead, you
  include it.

A class always needs to be instantiated, whereas a module does not.

```rb
# Bad Example
class Math
  def add(a, b)
    a + b
  end

  def subtract(a, b)
    a - b
  end
end
math = Math.new
sum = math.add(2, 2)
```

```rb
module Math
  def add(a, b)
    a + b
  end
  def subtract(a, b)
    a - b
  end
end
  class CashRegister
  include Math
  def calculate_change(total_cost, amount_paid)
    subtract(amount_paid, total_cost)
  end
end
```

## Chapter 3: Creating Quality Methods

### Parameters

Use Fewer Parameters

This function isn't alterable: we can make this better.

```rb
def greeting
  "Hello"
end
```

Now we can alter this:

```rb
def greeting(name)
  "Hello #{name}"
end
```

Remember that this can also be `nil`, so we should pay attention to this
case as well:

```rb
def greeting(name)
  "Hello #{name || 'unknown'}"
end
```

We can have a default argument in the function

```rb
def greeting(name = 'unknown')
  "Hello #{name}"
end
```

The passed in value can be an array or a hash or a long string too, so
you must be able to catch for those as well.

You'll want to use instance variables and attr_accessors and the like
liberally in classes.

```rb
class Config
  attr_accessor :num_players, :start_score

  def intiialize(num_players, start_score)
    @num_players = num_players
    @start_score = start_score
  end
end
```

### Parameter Order

- You should pass in parameters in an order that the caller would
  expect.

```rb
# bad
def login(password, username)
  # login
end

# good
def login(username, password)
  # login
end

# let them choose with a hash
def login(username:, password:)
  # login
end
```

Try to return the same type always, or throw an exception.

```rb
# Bad, because find_by_name ca return a hash or a string
class User
  attr_accessor :id, :name

  def initialize(id, name)
    self.id = id
    self.name = name
  end

  def find_by_name(users, name)
    users.each do |user|
      if user.name == name
        return user
      end
    end
    return { message: "Unable to find user with name #{name}" }
  end
end

class User
  attr_accessor :id, :name

  def initialize(id, name)
    self.id = id
    self.name = name
  end

  def find_by_name(users, name)
    users.each do |user|
      if user.name == name
        return user
      end
    end
    raise "could not find User"
  end
end
```

### Guard Clause

- If the data provided to a method is not valid, you will want to
  guard against that.

```rb
def clear(items)
  return if items.nil? || !items.is_a?(Array)

  items.each do |item|
    # clear the item
  end
end
```

### Method Length

- You'll not want a method to grow too long in length; try to make
  methods < 20 lines long.

- Try to create private helper methods in classes that might do
  validation.

```rb
# Bad
def create_user(first_name, last_name)
  raise ArgumentError, "First Name is required" unless first_name

  raise ArgumentError, "Last Name is required" unless last_name

  User.create(first_name: first_name, last_name: last_name)
end

# Good
def create_user(first_name, last_name)
  validate_input(first_name, last_name)
  User.create(first_name: first_name, last_name: last_name)
end
```

- Make method names short, but not too short.

```rb
# Bad
# Single Line
 def qualified_users
 User.where(active: true).select(&:qualified?).sort(&:last_login)
end

# Good
# Multiple Lines
def qualified_users
  active_users = User.where(active: true)
  qualified_users = active_users.select(&:qualified?)
  qualified_users.sort(&:last_login)
end
```

### Comments

- Make sure to comment why you're doing things, or notes for later.

```rb
def change_role(user_id, new_role)
  # find a user by id
  user = User.find(user_id)
   # check that current role does not equal the new role
  if user.role != new_role
  # assign new role to the user user.role = new_role
  end
 # end of method
end
```

#### Quality Comments

```rb
def change_role(user_id, new_role)
  user = User.find(user_id)
  role_service = RoleService.new(user)

  # Guard against cases where the role service can't assign.
  return unless role_service.can_assign(new_role)

  if user.role != new_role
    user.role = new_role
  end
end
```

#### Stale Comments

- Comments can cause problems if they are incorrect.
- Be sure to guard against these cases.

```rb
def fullname(first_name, last_name)
  # Confirm last_name is not blank or nil
  "#{first_name} #{last_name}".strip
end
```

#### Comments and Refactoring

- If you use comments to group related methods, you should break out
  the logic into smaller methods.

Instead of:

```rb
def accounts_from_file(file_path)
  # read lines from file
  file = File.new(file_path)
  lines = file.readlines

  # Create an account for each line
  accounts = lines.collect do |line|
  # Parse name and email
  account_info = line.parse(',')
  name = account_info[0]
  email = account_info[1]

  # Create an account using the parsed data
  Account.create(name: name, email: email)
  end
end
```

Try:

```rb
def accounts_from_file(file_path)
lines = read_file(file_path)
create_accounts(lines)
end

def read_file(file_path)
  file = File.new(file_path)
  file.readlines
end

def create_accounts(lines)
  accounts = lines.collect do |line|
    account_params = account_params_from_line(line)
    Account.create(account_params)
  end
end

def account_params_from_line(line)
  account_info = line.parse(',')
  { name: account_info[0], email: account_info[1] }
end
```

#### Nesting

- Avoid deep nesting:

```rb
MAX_PROMO_RATE = 5
def send_promo_email(user)
  if user.email.present?
    if user.promos_sent < MAX_PROMO_RATE
      UserMailer.promo_email(user).deliver
    end
  end
end
```

- Reduce nesting by creating helper methods

```rb
MAX_PROMO_RATE = 5
def send_promo_email(user)
  if can_send?(user)
    UserMailer.promo_email(user).deliver
  end
end

def can_send?(user)
  user.email.present? && user.promos_sent < MAX_PROMO_RATE
end
```

## Chapter 4 Using Boolean Logic

- try to create variables that are boolean statements.

```rb
class Player
  attr_accessor :time_until_spawn, :health
end
# Boolean logic directly in an IF statement
def respawn(player)
  if player.time_until_spawn <= 0 && player.health == 0
    respawn_at_base
  end
end

def respawn_at_base
  puts 'Player respawned at base'
end
player = Player.new player.time_until_spawn = 0 player.health = 0
respawn(player)
```

Instead, capture it in a variable:

```rb
class Player
  attr_accessor :time_until_spawn, :health
end

# Boolean logic stored in a variable
def respawn(player)
  ready_to_spawn = player.time_until_spawn <= 0 && player.health == 0
  respawn_at_base if ready_to_spawn
end
def respawn_at_base
  puts 'Player respawned at base'
end
player = Player.new player.time_until_spawn = 0 player.health = 0
respawn(player)
```

- combine with guard clauses.

```rb
def enable_editing
  user_exists = !user.nil? return if user_exists
  can_edit = user.editor? && !user.disabled?
  if user_exists && can_edit
    # code to enable editing
  end
end
```

#### Unless statements

- unless statements are the opposite of if statements.
- use them in guard clauses.

```rb
def check_resource(user_id, resource_id)
  return false unless User.find(user_id).can_access(resource_id)
  # check resource
```

#### Ternary Operators

- Use this once per line to simplify if/else expressions.

```rb
# Bad
if a > b
  result = a
else
  result = b
end

# Good
result = a > b ? a : b
```

#### Avoid Double Negatives

- Don't use a double negative

```rb
# bad
def is_not_found(book)
  found = self.books.include?(book)
  !found
end

# good
def is_found(book)
  self.books.include?(book)
end
```

#### Truthy and Falsy

- Everything that isn't nil or false is falsy.
- These evaluate to false.
- Everything else is truthy, and evaluates to true.

#### Single Ampersand

- Single ampersand evaluates both sides of its arguments.
- The doubly ampersand does not.

## Chapter 5 Classes

### Initialize Method

- when you call the .new method on a class, it executes the code in
  the `iniitalize` method.

- Leave complicated calculations outside of the `initialize` method.

- Try not to throw inside of the initialize method unless there is
  malformed data provided.

- Use instance variables to hoist state in ruby.

### Private Methods

- Use private methods to do calculations that aren't necessary for
  callers to understand.

```rb
class BankAccount
  def initialize(starting_balance)
    @balance = starting_balance
  end

  def display_balance
    format_for_display
  end

  private
  def format_for_display
    "Account Balance: #{@balance}"
  end
end
```

#### Modules

- Use modules for methods that shouldn't have to be instantiated.

```rb
module Math
  def add(a, b)
    a + b
  end
  def multiply(a, b)
    a * b
  end
end

class BankAccount
  include Math
  def initialize(balance, interest_rate)
    @balance = balance
    @interest = interest_rate
  end
  def add_to_balance(amount)
    @balance = add(@balance, amount)
  end
  def calculate_interest multiply(@balance, @interest_rate)
  end
end
```

- Try to use composition when possible, but inheritance has its place.
- Create a common class and embed that into each class.

```rb
class SuperMarket
  def initialize(accountant)
    @accountant = accountant
  end
end

class ToyStore
  def initialize(accountant)
    @accountant = accountant
  end
end

accountant = Accountant.new
toy_store = ToyStore.new(accountant) super_market = SuperMarket.new(accountant)
```

## Chapter 6: Refactoring

#### No change is too small.

#### Single Responsibility Principle

- make it so a method only does one thing.

## Chapter 7: Test Driven Development

- start with tests to implement your code.

- think about the ways your code might interact.
