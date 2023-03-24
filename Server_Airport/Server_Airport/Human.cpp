#include "Human.h"

void Human::setBirthday(Connection& connection)
{
	Date min, max;
	min.set(1, 1, 1900);
	max.setLocalDate();
	max.setYear(max.getYear() - 18);
	Date::checkInterval(birthday, min, max, connection);
}
