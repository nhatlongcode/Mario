#ifndef CABSTRACTSERVICE_H
#define CABSTRACTSERVICE_H


class CAbstractService
{
public:
	virtual void Init() = 0;
	virtual ~CAbstractService() = default;
};
typedef CAbstractService* LPService;
#endif

