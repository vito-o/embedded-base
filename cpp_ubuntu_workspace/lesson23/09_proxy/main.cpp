#include "Proxy.hpp"
#include "RealGirl.hpp"



int main(int argc, char const *argv[])
{
    Girl *girl = new RealGirl;
	Proxy *proxy = new Proxy;
    
    proxy->setMarryGirl(girl);

	proxy->marry(10);

	cout << "----------------" << endl;

	proxy->marry(10000);
    return 0;
}
