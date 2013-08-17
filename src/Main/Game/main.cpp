#include <iostream>
#include <conio.h>

using namespace std;

#include <boost\thread.hpp>
#include <Utilities\utilities.h>

class Fish
{
public:
	Fish()
	{
		m_position = -1;
		m_name = "NOT INITIALIZED";
		m_icon = 7;
	}

	~Fish(){}
	
	int init(int a_pos, char * a_name, char a_icon)
	{
		m_position = a_pos;
		m_name = a_name;
		m_icon = a_icon;
		return 0;
	}

	void swim()
	{
		m_position++;
		if(m_position > 10)
			m_position = 0;
	}

	void draw()
	{
		for(int i = 0; i < m_position; ++i)
			printf(" ");
		printf("%c", m_icon);
		printf("\n");
	}

	char * getName(){ return m_name; }
	int getPosition(){ return m_position; }

private:
	int				m_position;
	char *			m_name;
	char			m_icon;
};

int main()
{
	Fish f;
	f.init( 2, "CHARLY", 22 );
	for(int i = 0; i < 100; ++i)
	{
		f.swim();
		f.draw();
	}
	/*
	int testf = utest_function();
	Foo f;
	boost::thread test(boost::bind(&Foo::some_function, &f));
	test.start_thread();
	// added comment
	printf("Hello World!!!");	
	*/
	return 0;
}