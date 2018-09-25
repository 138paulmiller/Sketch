#pragma once


//stackable singletons that can be globally pushed, poppd

#define Stackable(Type)				\
	static Type  current();			\
	static void push(Type t);		\
	static void pop();				\
	static void	destroy();			\
	static void	init();				\

