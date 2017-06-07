#ifndef CORE_H
#define CORE_H
class Core{
	public:
		Core();
		void think();
		void listen();
		map <string,string> triggers;
		Module modules;
};
#endif