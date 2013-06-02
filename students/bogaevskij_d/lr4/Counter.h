#ifndef _Counter
#define _Counter
class Counter{   //счетчик
	private:
		int number;
		bool active;
	public:
		Counter(){number=0; active=0;}
		void on(void){active=1; number=0;}
		void off(void){active=0;}
		void inc(void){if(active)number++;}
		int get_number(void){if(!active) return number;}
	};
#endif