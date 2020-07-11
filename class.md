## Why we need functions?

- It is the essential building blocks of every program

```cpp
class C {
public:
	void foo(int i);
private:
	std::string s;
};
```

```c
struct C {
	std::string s;
};

void foo(C* c, int i);
```

```cpp
class B {
public:
	virtual void foo(int i);
	virtual void bar(int i);
};

class D : public B {
public:
	void foo(int i) override;
};
```

```c
void B__foo(B* b, int i);
void B__bar(B* b, int i);
void D__foo(D* d, int i);

struct B {
	__vtable[2] { B__foo, B__bar };
};

struct D {
	__vtable[2] { D__foo, B__bar };
};
```

## How long a function should be?

- It depends
- Single Responsibility Principle (SRP) 

```cpp
// foo does this and that
void foo();
	
void bar() {
	// comment
	code;

	// comment
	code;

	// comment
	code;
}
```

## How to pass argument(s)

- `foo(T)` for small(~20ish bytes?) objects what won't ![p1](https://godbolt.org/z/RD4VoS)
- `foo(T&)` and `foo(T const&)` for larger objects, or uncopyable
- `foo(T*)` and `foo(T const*)` for ==optional== larger objects, std::optional<T>?
- `foo(T&&)` for optimization

That's it!

## dig deeper

```cpp
// .hpp
void foo(T);

// .cpp
void foo(T const);
```

```cpp
void bar(S);

S foo();
bar(foo()); // copy elision, zero cost

S s;
bar(s);     // copy, can be expensive
```

```cpp
void foo(S*);
void foo(std::optional<S>); // by value and optional, kinda immutable

auto p = std::optional<S*>(nullptr);
if(! p)	         // flase, p has a value
if(p == nullptr) // true, the value is nullptr
```

## How about smart pointers

Prefer value/pointer/reference

```cpp
void by_value(T);

void by_ptr(T*);
void by_cptr(T const*);

void by_ref(T&)
void by_cref(T const&)

auto p = smart_ptr_type<T>();

by_value(T);

by_ptr(p.get());
by_cptr(p.get());

by_ref(*p);
by_cref(*p);
```

Only use smart pointers you may need to manipulate ownerships

```cpp
void foo(std::unique_ptr<T>);

auto p = std::make_unique<T>();

foo(std::move(p));
```

```cpp
void foo(std::unique_ptr<T>&&);

auto p = std::make_unique<T>();

foo(std::move(p));
```

```cpp
void foo(std::unique_ptr<T> &);

auto p = std::make_unique<T>();

foo(p);
```

```cpp
void foo(std::shared_ptr<T> &);

auto p = std::make_shared<T>();

foo(p);
```

| #           |                                             |
|-------------|---------------------------------------------|
| snapshot    | `T`                                         |
| modify      | `T*`, `T&`                                  |
| observe     | `T const*`, `T const&`                      |
| sink        | `std::unique_ptr<T>` `std::unique_ptr<T>&&` |
| may reseat  | `std::unique_ptr<T>&` `std::shared_ptr<T>&` |
| keep alive  | `std::shared_ptr<T>`                        |
| performance | `T&&`                                       |

`std::smart_ptr<T>&` can be dangerous

>R.37: Do not pass a pointer or reference obtained from an aliased smart pointer

```cpp
auto gp = std::make_shared<T>();

void foo(T*);

void bar(std::shared_ptr<T>& p) {
	// some code

	foo(p.get());
}

bar(gp);
```

```cpp
void bar1(std::shared_ptr<T> p) {
	foo(p.get());
}

void bar2(std::shared_ptr<T>& p) {
	auto c = p;
	foo(c.get());
}

// more cumbersome to std::unique_ptr
```

## Herb Sutter's favorite 10-liner

`std::weak_ptr<T>` means temporary shared ownership

```cpp
std::shared_ptr<widget> get_widget(int id) {
	static std::map<int, std::weak_ptr<widget>> cache;
	static std::mutex m;

	std::lock_guard<std::mutex> hold(m);
	auto sp = cache[id].lock();
	if (!sp) cache[id] = sp = load_widget(id);
	return sp;
}
```

Move semantics solves these and *may* provide a performance boost

```cpp
struct S { int a[1000]; }; // no owned resources

struct S { std::string s; }; // with SSO, the performance is no better than copy
```

## High order functions

![nvi](https://godbolt.org/z/1e613x)

![init version](https://godbolt.org/z/MZH3sS)
![done version](https://godbolt.org/z/6veSNr)

## Aliasing

![code](https://godbolt.org/z/16Tcv6)

That's why most xxx_cast you see is undefined behavior

- pass by value when you can, pass by const ref when you must</li>
- use raw pointer for optional, unique_ptr/shared_ptr for lifetime</li>
- don't share with \* or &, express via shared_ptr</li>

					<section>
						<pre><code class="cpp" data-trim data-noescape>
						S foo() { S s; return s; }

						S foo(S s) { return s; }

						S foo(S x, S y) { return test ? std::move(x) : std::move(y); }

						S foo(S x, S y) { if (test) return x; else return y; }
						</code></pre>
					</section>
					<section>
						<pre><code class="cpp" data-trim data-noescape>
						S foo() { S s; return std::move(s); }

						S foo() { S &amp;s = make_S(); return s; }

						S foo(S&amp; s) { return s; }

						S foo(S x, S y) { return test ? x : y; }
						</code></pre>
					</section>
				</section>
				<section>
					<section>
						<pre><code class="cpp" data-trim data-noescape>
						std::unique_ptr&lt;S&gt; foo();
						</code></pre>
					</section>
				</section>
			</div>
		</div>

		<script src="js/reveal.js"></script>

		<script>
			Reveal.initialize({
				width: 1440,
				slideNumber: true,
				loop: true,
				hash: true,
				fragmentInURL: true,
				transition: 'none',
				backgroundTransition: 'none',
				autoPlayMedia: true,
				dependencies: [
					{ src: 'plugin/markdown/marked.js' },
					{ src: 'plugin/markdown/markdown.js' },
					{ src: 'plugin/notes/notes.js', async: true },
					{ src: 'plugin/zoom-js/zoom.js', async: true },
					{ src: 'plugin/highlight/highlight.js', async: true }
				]
			});
		</script>
	</body>
</html>
