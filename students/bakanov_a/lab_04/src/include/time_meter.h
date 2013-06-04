#ifndef _TIME_METER_H
#define _TIME_METER_H

#include <ctime>

/**
 * @brief	Удобный класс для замера времени.
 */
class TimeMeter
{
public:
	/**
	 * @brief	Инициализирующая функция. Ее следует вызывать первой.
	 */
	static void init();
	/**
	 * @brief	Функция возвращает время в секундах, прошедшее с последнего
	 * вызова TimeMeter::init или TimeMeter::getPastTime.
	 */
	static float getPastTime();

private:
	static clock_t lastTime;
};

#endif /* _TIME_METER_H */
