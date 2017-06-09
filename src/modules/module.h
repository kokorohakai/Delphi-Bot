#ifndef MODULE_H
#define MODULE_H
class Module{
	public:
		Module();
		DiscordModule discordModule;
		//shared methods
		virtual void listen();
};
#endif