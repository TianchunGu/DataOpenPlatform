all:demo01 demo02 demo03 incache outcache

demo01:demo01.cpp _public.h _public.cpp
	g++ -g -o demo01 demo01.cpp _public.cpp

demo02:demo02.cpp _public.h _public.cpp
	g++ -g -o demo02 demo02.cpp _public.cpp

demo03:demo03.cpp _public.h _public.cpp
	g++ -g -o demo03 demo03.cpp _public.cpp

incache:incache.cpp _public.h _public.cpp
	g++ -g -o incache incache.cpp _public.cpp

outcache:outcache.cpp _public.h _public.cpp
	g++ -g -o outcache outcache.cpp _public.cpp

clean:
	rm -f demo01 demo02 demo03 incache outcache