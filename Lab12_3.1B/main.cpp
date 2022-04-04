#include <iostream>
#include <string>
#include <Windows.h>
#include <iomanip>
using namespace std;

#pragma region "Прізвища студентів"
string surnames[] =
{
	"Бурачинський",
	"Кваша",
	"Попенко",
	"Жученко",
	"Пероганич",
	"Карпінський",
	"Дроб\'язко",
	"Боровий",
	"Приступа",
	"Костюк",

	"Гайдук",
	"Грицина",
	"Балога",
	"Величковська",
	"Марченко",
	"Бершеда",
	"Лимаренко",
	"Кравченко",
	"Ластівка",
	"Бельська",
};
#pragma endregion

enum class Spec { KN, II, ME, PI, PE };
string strSpec[] = { "Компютерні науки", "Інформатика", "Математика та економіка", "Фізика та інформатика", "Трудове навчання" };

struct Student
{
	string surname;
	int course;
	Spec spec;
	double mark_physic;
	double mark_math;
	union
	{
		double mark_programic;
		double mark_chisel_method;
		double mark_pedagogic;
	} mark_last;
};

//void Create(Student* s, size_t cnt)
//{
//	for (size_t i = 0; i < cnt; i++)
//	{
//		cin.get();
//		cout << "Прізвище студента: ";
//		getline(cin, s[i].surname);
//		cout << "Курс(1-6): "; cin >> s[i].course;
//		int spec;
//		cout << "Спеціальність(0 - Програмне забезпечення, 1 - Інформаційні технології, 2 - Компютерні науки, 3 - Автомобільного транспорту): "; cin >> spec;
//		s[i].spec = (Spec)spec;
//		cout << "Оцінка з фізики: "; cin >> s[i].mark_physic;
//		cout << "Оцінка з математики: "; cin >> s[i].mark_math;
//		cout << "Оцінка з інформатики: "; cin >> s[i].mark_informatic;
//	}
//}

void Generate(Student* s, size_t cnt)
{
	for (size_t i = 0; i < cnt; i++)
	{
		s[i].surname = surnames[rand() % 20];
		s[i].course = 1 + rand() % 6;
		s[i].spec = Spec(rand() % 4);
		s[i].mark_physic = (30 + rand() % 20) / 10.0;
		s[i].mark_math = (30 + rand() % 20) / 10.0;
		s[i].mark_last.mark_programic = (30 + rand() % 20) / 10.0;
	}
}

void Display(Student* s, size_t cnt)
{
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << "|  №  | курс |    прізвище    |       спеціальність     | фізика | математика | Прогр. | Чис. мет. | Педаг. |" << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	cout << left;
	for (size_t i = 0; i < cnt; i++)
	{
		cout << "|" << setw(5) << i << "|"
			<< setw(6) << s[i].course << "|"
			<< setw(16) << s[i].surname << "|"
			<< setw(25) << strSpec[int(s[i].spec)] << "|"
			<< setw(8) << s[i].mark_physic << "|"
			<< setw(12) << s[i].mark_math << "|";
		if (s[i].spec == Spec::KN)
			cout << setw(8) << s[i].mark_last.mark_programic;
		else
			cout << setw(8) << " ";
		cout << "|";
		if (s[i].spec == Spec::II)
			cout << setw(11) << s[i].mark_last.mark_chisel_method;
		else
			cout << setw(11) << " ";
		cout << "|";
		if (s[i].spec != Spec::KN && s[i].spec != Spec::II)
			cout << setw(8) << s[i].mark_last.mark_pedagogic;
		else
			cout << setw(8) << " ";
		cout << "|" << endl;
	}
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
}

double avgMark(Student s)
{
	return (s.mark_last.mark_programic + s.mark_math + s.mark_physic) / 3.;
}

int CountStudent(Student* s, size_t cnt)
{
	int count = 0;
	for (size_t i = 0; i < cnt; i++)
	{
		if (avgMark(s[i]) > 4.5)
			count++;
	}
	return count;
}

enum class Mark { math, physic, programic, chisel_method, pedagogic, nothing };
string strMark[] = { "математика", "фізика", "програмування", "чисельних методів", "педагогіка"};
void BestSubject(Student* s, size_t cnt, Mark mark[5])
{
	double math = 0, physic = 0, prog = 0, meth = 0, ped = 0;
	size_t cnt_prog = 0, cnt_meth = 0, cnt_ped = 0;
	for (size_t i = 0; i < cnt; i++)
	{
		math += s[i].mark_math;
		physic += s[i].mark_physic;
		if (s[i].spec == Spec::KN) {
			prog += s[i].mark_last.mark_programic;
			cnt_prog++;
		}
		if (s[i].spec == Spec::II) {
			meth += s[i].mark_last.mark_chisel_method;
			cnt_meth++;
		}
		if (s[i].spec != Spec::KN && s[i].spec != Spec::II) {
			ped += s[i].mark_last.mark_pedagogic;
			cnt_ped++;
		}
	}
	math /= cnt;
	physic /= cnt;
	prog /= cnt_prog;
	meth /= cnt_meth;
	ped /= cnt_ped;

	for (size_t i = 0; i < 5; i++)
		mark[i] = Mark::nothing;

	double m = math;
	int i = 0;
	mark[i] = Mark::math;
	if (physic > m)
	{
		m = physic;
		mark[i] = Mark::physic;
	}
	if (prog > m)
	{
		m = prog;
		mark[i] = Mark::programic;
	}
	if (meth > m)
	{
		m = meth;
		mark[i] = Mark::chisel_method;
	}
	if (ped > m)
	{
		m = ped;
		mark[i] = Mark::pedagogic;
	}

	if (m == math && mark[i] != Mark::math)
		mark[++i] = Mark::math;
	if (m == physic && mark[i] != Mark::physic)
		mark[++i] = Mark::physic;
	if (m == prog && mark[i] != Mark::programic)
		mark[++i] = Mark::programic;
	if (m == meth && mark[i] != Mark::chisel_method)
		mark[++i] = Mark::chisel_method;
	if (m == ped && mark[i] != Mark::pedagogic)
		mark[++i] = Mark::pedagogic;
}

int main()
{
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	size_t cnt;
	cout << "Введіть кількість студентів у масиві: "; cin >> cnt;
	Student* s = new Student[cnt]();

	Generate(s, cnt);
	Display(s, cnt);
	cout << "Кількість студентів, середній бал яких вищий за 4,5: " << CountStudent(s, cnt) << endl;
	Mark mark[5];
	BestSubject(s, cnt, mark);
	cout << "Предмет, середній бал якого найбільший: ";
	for (size_t i = 0; i < 5; i++)
		if (mark[i] != Mark::nothing)
			cout << strMark[int(mark[i])] << " ";

	delete[] s;

	return 0;
}