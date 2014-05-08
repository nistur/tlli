TLLI - Tiny Little Lisp Interpeter
==================================

This is just an experimentation at writing a lisp. I doubt it will ever be anywhere near usable. It's horrendously inefficient. It lacks a huge amount of features. But I don't care. That's not why I wrote it.

Current "features" include:
+
-
*
/
defun

And that's it.

Issues
------

Too many to list.
Seriously.

However, one major thing I would like to change, apart from the lack of features, is that it does all the interpretation at runtime, live. That's a lot of string manipulation. Ideally I'd like to create some intermediate bytecode format. That would mean I could write out binary files too which I would like.

Also the code is hideous. Written on a train journey and three bus journeys (and counting)

Oh, and it leaks memory, I'm yet to write a garbage collector.