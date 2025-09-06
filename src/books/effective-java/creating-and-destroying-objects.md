---
title: Creating and Destroying Objects
date created: Tuesday, August 5th 2025, 10:44:59 am
date modified: Tuesday, August 5th 2025, 11:21:04 am
---

# Creating and Destroying Objects

Prev: [introduction](introduction.md)
Next: [methods-common-to-all-objects](methods-common-to-all-objects.md)

# 1: Consider Static Factory Methods instead of Constructors

Normally, clients can obtain an instance with a public constructor. However, there's also a static factory method, which returns an instance of the class.

```java
public static Boolean valueOf(boolean b) {
	return b ? Boolean.TRUE : Boolean.FALSE;
}
```

They have some pros
1. They're named (constructors are unnamed and overloadable)
2. They don't have to create a new object
3. They can return an object that is a subtype of the return type (I would prefer being specific about the return type).

Some common names:

- `from`: 
```java
Date d = Date.from(instant);
```
- `of`:
```java
Set<Rank> faceCards = EnumSet.Of(JACK, QUEEN, KING);
```
- `valueOf`:
```java
BigInteger prime = BigInteger.valueOf(Integer.MAX_VALUE);
```
- `instance` or `getInstance`:
```java
StackWalker luke = StackWalkver.getInstance(options);
```
- `create` or `newInstance`:
```java
Object newArray = Array.newInstance(classObject, arrayLen);
```

I think this makes sense, since overloading constructors can be quite hard to read in general, and you may want constructors that convert or do other things.

# 2. Consider a Builder when Faced with Many Constructor Parameters

When you have a class that has a lot of parameters, you might use the telescoping constructor pattern, where you have one constructor with the required parameters, one with a single optional parameter, etc.

This is verbose and hard to maintain. Every new optional parameter requires a corresponding constructor. Also all these types are int, which allows a caller to mix up the parameter order.

```java
public class NutritionFacts {
	private final int servingSize; // (mL) required
	private final int servings; // (per container) required
	private final int calories; // (per serving) optional
	private final int fat; // (g/serving) optional
	private final int sodium; // (mg/serving) optional
	private final int carbohydrate; // (g/serving) optional
	
	public NutritionFacts(int servingSize, int servings) {
		this(servingSize, servings, 0);
	}
	public NutritionFacts(int servingSize, int servings, int calories) {
		this(servingSize, servings, calories, 0);
	}
	public NutritionFacts(int servingSize, int servings, int calories, int fat) {
		this(servingSize, servings, calories, fat, 0);
	}
	public NutritionFacts(int servingSize, int servings, int calories, int fat, int sodium) {
		this(servingSize, servings, calories, fat, sodium, 0);
	}
	public NutritionFacts(int servingSize, int servings, int calories, int fat, int sodium, int carbohydrate) {
		this.servingSize = servingSize;
		this.servings = servings;
		this.calories = calories;
		this.fat = fat;
		this.sodium = sodium;
		this.carbohydrate = carbohydrate;
	}
}
```

You can also do the JavaBeans pattern, where you use setters to create an object:

```java
public class NutritionFacts {
	// Parameters initialized to default values (if any)
	private int servingSize = -1; // Required; no default value
	private int servings = -1; // Required; no default value
	private int calories = 0;
	private int fat = 0;
	private int sodium = 0;
	private int carbohydrate = 0;
	public NutritionFacts() { }
	
	// Setters
	public void setServingSize(int val) { servingSize = val; }
	public void setServings(int val) { servings = val; }
	public void setCalories(int val) { calories = val; }
	public void setFat(int val) { fat = val; }
	public void setSodium(int val) { sodium = val; }
	public void setCarbohydrate(int val) { carbohydrate = val; }
}
```

```java
NutritionFacts cocaCola = new NutritionFacts();
cocaCola.setServingSize(240); // invalid here 
cocaCola.setServings(8);
cocaCola.setCalories(100);
cocaCola.setSodium(35);
cocaCola.setCarbohydrate(27);
```

However, you can create an invalid object (after the first `setServingSize`), and then use it, which is confusing.

To avoid this, use the builder pattern:

```java
public class NutritionFacts {
	private final int servingSize;
	private final int servings;
	private final int calories;
	private final int fat;
	private final int sodium;
	private final int carbohydrate;
	public static class Builder {
		// Required parameters
		private final int servingSize;
		private final int servings;
		// Optional parameters - initialized to default values
		private int calories = 0;
		private int fat = 0;
		private int sodium = 0;
		private int carbohydrate = 0;
		public Builder(int servingSize, int servings) {
			this.servingSize = servingSize;
			this.servings = servings;
		}
		public Builder calories(int val) { calories = val; return this; }
		public Builder fat(int val) { fat = val; return this; }
		public Builder sodium(int val) { sodium = val; return this; }
		public Builder carbohydrate(int val) { carbohydrate = val; return this; }
		public NutritionFacts build() {
			return new NutritionFacts(this);
		}
	}
	private NutritionFacts(Builder builder) {
		servingSize = builder.servingSize;
		servings = builder.servings;
		calories = builder.calories;
		fat = builder.fat;
		sodium = builder.sodium;
		carbohydrate = builder.carbohydrate;
	}
}
```

With a private constructor, you can't directly initialize NutritionFacts, and instead have to go through the Builder class. You then create an instance of the NutritionFacts object:

```java
NutritionFacts cocaCola = new NutritionFacts.Builder(240, 8)
.calories(100).sodium(35).carbohydrate(27).build();
```

I think this pattern is good, however, I don't like requiring a "Builder" class instead of building the actual class. I think this would be better without needing to write another class.

# 3: Enforce the Singleton Property with a Private Constructor or an Enum Type

A Singleton is a class that is instantiated once. You can use a final field to make one:

```java
// Singleton with public final field
public class Elvis {
	public static final Elvis INSTANCE = new Elvis();
	private Elvis() { ... }
	public void leaveTheBuilding() { ... }
}
```

Or a static factory method:

```java
// Singleton with static factory
public class Elvis {
	private static final Elvis INSTANCE = new Elvis();
	private Elvis() { ... }
	public static Elvis getInstance() { return INSTANCE; }
	public void leaveTheBuilding() { ... }
}
```

Or you can use an enum singleton, which allows you to create singletons and guarantee serialization.

```java
// Enum singleton - the preferred approach
public enum Elvis {
	INSTANCE;
	public void leaveTheBuilding() { ... }
}
```

Makes sense but I'd rather avoid these as much as possible and use a locator or something else.

# 4. Enforce Noninstantiability with a Private Constructor

Some classes weren't meant to be instantiated. You can include a private constructor and make it uninstantiable. This also prevents this from being subclassed.

```java
// Noninstantiable utility class
public class UtilityClass {
	// Suppress default constructor for noninstantiability
	private UtilityClass() {
		throw new AssertionError();
	}
}
```

# 5. Prefer Dependency Injection to Hardwiring Resources

Sometimes your classes will rely on an underlying resource:

```java
// Inappropriate use of static utility - inflexible & untestable!
public class SpellChecker {
	private static final Lexicon dictionary = ...;
	private SpellChecker() {} // Noninstantiable
	public static boolean isValid(String word) { ... }
	public static List<String> suggestions(String typo) { ... }
}
```

Instead of hardwiring it in the class, you should allow it to be passed in construction:

```java
// Dependency injection provides flexibility and testability
public class SpellChecker {
	private final Lexicon dictionary;
	public SpellChecker(Lexicon dictionary) {
		this.dictionary = Objects.requireNonNull(dictionary);
	}
	public boolean isValid(String word) { ... }
	public List<String> suggestions(String typo) { ... }
}
```

This makes it easier to test. You can use DI libraries like Dagger, Guice, or Spring.

# 6. Avoid Creating Unnecessary Objects

If you don't need to create an object, use a primitive type. If you do need to make an object, cache it:

```java
// Reusing expensive object for improved performance
public class RomanNumerals {
	private static final Pattern ROMAN = Pattern.compile("^(?=.)M*(C[MD]|D?C{0,3})" + "(X[CL]|L?X{0,3})(I[XV]|V?I{0,3})$");
	static boolean isRomanNumeral(String s) {
		return ROMAN.matcher(s).matches();
	}
}
```

Also watch out for autoboxing, where a primitive is boxed for you without a cast, incurring an allocation:

```java
// Hideously slow! Can you spot the object creation?
private static long sum() {
	Long sum = 0L;
	for (long i = 0; i <= Integer.MAX_VALUE; i++) {
		sum += i;
	}
	return sum;
}
```

# 7. Eliminate Obsolete Object References

There's a memory leak in this code:

```java
// Can you spot the "memory leak"?
public class Stack {
	private Object[] elements;
	private int size = 0;
	private static final int DEFAULT_INITIAL_CAPACITY = 16;
	public Stack() {
		elements = new Object[DEFAULT_INITIAL_CAPACITY];
	}
	public void push(Object e) {
		ensureCapacity();
		elements[size++] = e;
	}
	public Object pop() {
		if (size == 0)
		throw new EmptyStackException();
		return elements[--size];
	}
	/**
	* Ensure space for at least one more element, roughly
	* doubling the capacity each time the array needs to grow.
	*/
	private void ensureCapacity() {
		if (elements.length == size)
			elements = Arrays.copyOf(elements, 2 * size + 1);
	}
}
```

When popping from the stack, the objects popped off the stack are not nulled out, so they are held by the stack, and thus, not GCed. If you add:

```java
elements[size] = null;
```

Then the references will be GC'ed. Note that this should only be done if the class manages its own memory.

# 8. Avoid Finalizers and Cleaners

Finalizers and cleaners clean up resources, but they don't have guaranteed execution at the time and have performance penalties.

# 9. Prefer `try-with-resources` to `try-finally`

This `try-finally` is ugly with more than one resource.

```java
// try-finally is ugly when used with more than one resource!
static void copy(String src, String dst) throws IOException {
	InputStream in = new FileInputStream(src);
	try {
		OutputStream out = new FileOutputStream(dst);
		try {
			byte[] buf = new byte[BUFFER_SIZE];
			int n;
		while ((n = in.read(buf)) >= 0)
			out.write(buf, 0, n);
		} finally {
			out.close();
		}
	} finally {
		in.close();
	}
}
```

Instead, use `try-with-resources`

```java
// try-with-resources on multiple resources - short and sweet
static void copy(String src, String dst) {
	try (InputStream in = new FileInputStream(src);
	OutputStream out = new FileOutputStream(dst)) {
		byte[] buf = new byte[BUFFER_SIZE];
		int n;
		while ((n = in.read(buf)) >= 0)
		out.write(buf, 0, n);
	} catch (IOException e) { // catch IOExceptions
		return; // swallow IOExceptions
	}
}
```

Prev: [introduction](introduction.md)
Next: [methods-common-to-all-objects](methods-common-to-all-objects.md)
