#ifndef GUARD__SocketLibrary_hpp__
#define GUARD__SocketLibrary_hpp__

#if defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-sgd.lib")
#elif defined(_DEBUG) && defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-gd.lib")
#elif !defined(_DEBUG) && !defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt-s.lib")
#elif !defined(_DEBUG) && defined(_DLL)
#pragma comment (lib,"SocketLibrary-mt.lib")
#endif

class SocketLibrary
{
};

#endif