#ifndef _village_h_
#define _village_h_

class Village
{
    private:
		int count_vil;
		int count_post;
		int *coordinates;
		int result_size;
		int *result_coordinats;
	    void calculation(); 
    public:
		bool from_file();
		bool from_keyboard();
		void main_function();
		void save_to_file();
		void print_on_screen();

};

#endif
