#ifndef MODULE_H
#define MODULE_H
class Module{
	public:
		Module();
		static vector <Module *> modules;
		void load();
		//shared methods
		virtual void listen();
};
#endif