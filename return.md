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
