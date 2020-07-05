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

- `foo(T)` for small(~20ish bytes?) objects what won't change
- `foo(T&)` and `foo(T const&)` for larger objects
- `foo(T*)` and `foo(T const*)` for ==optional== larger objects, std::optional<T>?
- `foo(T&&)` for optimization

That's it!

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

| #          |                                              |
|------------|----------------------------------------------|
| snapshot   | `T`                                          |
| modify     | `T*`, `T&`                                   |
| sink       | `std::unique_ptr<T>`, `std::unique_ptr<T>&&` |
| reseat     | `std::unique_ptr<T>&`, `std::shared_ptr<T>&` |
| keep alive | `std::shared_ptr<T>`                         |
| bonus      | `T&&`                                        |

`std::smart_ptr<T>&` can be dangerous

>R.37: Do not pass a pointer or reference obtained from an aliased smart pointer

```cpp
auto gp = std::make_shared<T>();

void foo(T*);

void bar(std::shared_ptr<T>& p) {
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


				<section>
					<section>
						<p>Passing by value</p>
						<ul>
							<li>Built-in types</li>
							<li>Small to medium objects, always benchmark</li>
							<li>When copying is mandatory</li>
						</ul>
						<pre><code class="cpp" data-trim data-noescape>
						void foo(T const&amp; t) {
							;;;
							auto c = t;
							;;;
						}

						void foo(T t);
						</code></pre>
						<a href="https://godbolt.org/z/RD4VoS">const</a>
					</section>
					<section>
						<pre><code class="cpp" data-trim data-noescape>
						// .hpp
						void foo(T);

						// .cpp
						void foo(T const);
						</code></pre>
					</section>
					<section>
						<pre><code class="cpp" data-trim data-noescape>
						void bar(S);

						S foo();
						bar(foo()); // copy elision, zero cost

						S s;
						bar(s);     // copy, can be expensive
						</code></pre>
					</section>
				</section>
				<section>
					<section>
						<h2>Value Category</h2>
					</section>
				</section>
				<section>
					<section>
						<ul>
							<li>Something should not or can not be copied</li>
							<li>Has to be a pointer/reference in container or being passed as a parameter</li>
						</ul>
						<p>Move semantics solves these and <strong>may</strong> provide a performance boost</p>
						<pre class="fragment"><code class="cpp" data-trim data-noescape>
						struct S { int a[1000]; }; // no owned resources

						struct S { std::string s; }; // with SSO, the performance is no better than copy
						</code></pre>
					</section>
				</section>
				<section>
					<section>
						<p>Passing by reference</p>
						<ul>
							<li>When copying/moving is expensive</li>
							<li>When parameter is required</li>
						</ul>
						<pre><code class="cpp" data-trim data-noescape>
						void may_modify(S&amp;);
						void observe(S const&amp;);

						auto p = std::smart_pointer&lt;S&gt;();
						foo(*p);
						bar(*p);
						</code></pre>
					</section>
				</section>
				<section>
					<section>
						<p>Passing by non-owning pointer</p>
						<ul>
							<li>When copying/moving is expensive</li>
							<li>When parameter is optional</li>
							<li>Should never be an output parameter</li>
						</ul>
						<pre><code class="cpp" data-trim data-noescape>
						void foo(S*);
						void bar(S const*);

						auto p = std::smart_pointer&lt;S&gt;();
						foo(p.get());
						bar(p.get());
						</code></pre>
					</section>
					<section>
						<pre><code class="cpp" data-trim data-noescape>
						void foo(S*);
						void foo(std::optional<S>); // by value and optional, kinda immutable
						</code></pre>
						<pre clas="fragment"><code class="cpp" data-trim data-noescape>
						auto p = std::optional&lt;S*&gt;(nullptr);
						if(! p)	         // flase, p has a value
						if(p == nullptr) // true, the value is nullptr
						</code></pre>
					</section>
				</section>
				<section>
					<p>passing by <code>std::unique_ptr</code></p>
					<pre><code class="cpp" data-trim data-noescape>
					std::unique_ptr&lt;S&gt; bar();
					std::unique_ptr&lt;S&gt; s;

					void sink(std::unique_ptr&lt;S&gt;); // herb sutter
					foo(std::move(s));
					foo(bar());

					void sink(std::unique_ptr&lt;S&gt;&amp;&amp;); // scott meyers
					foo(std::move(s));
					foo(bar());
					</code></pre>
					<pre><code class="cpp" data-trim data-noescape>
					void may_reset(std::unique_ptr&lt;S&gt;&amp;);
					void foo(std::unique_ptr&lt;S&gt; const&amp;); // why?
					</code></pre>
				</section>
				<section>
					<p>passing by <code>std::shared_ptr</code></p>
					<p>smart pointers pass by reference is a reset</p>
					<ul>
						<li><code>std::shared_ptr</code> shouldn't be your default choice</li>
						<li><code>std::make_shared</code> is better than <code>std::shared_ptr, normally</ptr></li>
					</ul>
					<pre><code class="cpp" data-trim data-noescape>
					void foo(std::shared_ptr&lt;S&gt;); // something down the line may take ownership
					void foo(std::shared_ptr&lt;S&gt; const&amp; s) { // better
						start_thread(s);
					}
					// unique_ptr const &amp; doesn't make sense

					// multi threading
					void thread_fun(std::shared_ptr&lt;S&gt;); // ?

					void thread_fun(std::shared_ptr&lt;S const&gt;); // OK
					</code></pre>
					<pre><code class="cpp" data-trim data-noescape>
					std::shared_ptr&lt;S&gt; foo() { return std::make_shared&lt;S&gt;(); }

					std::unique_ptr&lt;S&gt; foo();
					auto p = std::shared_ptr&lt;S&gt;(foo()); // cannot do with make_shared
					</code></pre>

					<pre><code class="cpp" data-trim data-noescape>
					void share(std::shared_ptr&lt;S&gt;);
					void may_reset(std::shared_ptr&lt;S&gt;&amp;);
					void may_share(std::shared_ptr&lt;S&gt; const&amp;);
					</code></pre>

					<p>Don't pass smart pointers by value/reference unless you want to manipulate it's ownership</p>

				</section>
				<section>
					<ul>
						<li>It is read-only view</li>
						<li>Doesn't alter lifetime of the data</li>
						<li>Cheap to copy</li>
					</ul>
				</section>
				<section>
					<p>How about <code>&amp;&amp;</code></p>
					<a href="https://godbolt.org/z/NKHcs6">performance</a>
				</section>
				<section>
					<p>Aliasing</p>
					<a href="https://godbolt.org/z/_8iLFA">code</a>
					<p class="fragment">That's why most xxx_cast you see is undefined behavior</p>
					<!-- static_cast UB in radius -->
				</section>
				<section>
					<ul>
						<li>pass by value when you can, pass by const ref when you must</li>
						<li>use raw pointer for optional, unique_ptr/shared_ptr for lifetime</li>
						<li>don't share with * or &amp;, express via shared_ptr</li>
					</ul>
				</section>
				<section>
					<section>
						<ul>
							<li>By default, return by value</li>
							<li>RVO has zero cost</li>
						</ul>
					</section>
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
