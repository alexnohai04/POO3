//TEMA 6
#include <iostream>
#include <string>
#include <vector>
#include <exception>
#include "clase.h"
int main()
{
	std::cout << "Bine ati venit la aplicatia de gestiune a abonamentelor!\n";
	bool loop = 1;
	connection_pool pool;
	Clienti& clienti = Clienti::getInstance();
	while (loop) {
		std::cout << "Alege o actiune!\n";
		std::cout << "1. Adaugare abonati\n";
		std::cout << "2. Afisare abonati\n";
		std::cout << "3. Numar abonamente (Total/Premium)\n";
		std::cout << "4. Suma totala incasata\n";
		std::cout << "5. Iesire\n";
		std::cout << "6. Clear\n";
		int optiune;
		std::cout << "Introduceti optiunea:";
		std::cin >> optiune;
		while (optiune < 1 || optiune > 6)
		{
			std::cout << "Introduceti optiunea:";
			std::cin >> optiune;
		}

		try {
			switch (optiune) {
			case 1: {
				Abonat a1;
				try {
					connection& c = pool.get_conn();
					std::cout << "\nIntroduceti datele abonatului:\n";
					a1.citire();
					clienti.adaugaAbonat(a1);
					std::cout << "\nFelicitari! Ati adaugat un abonat cu succes!\n";
				}
				catch (Exceptie<std::string>& e) {
					std::cout << e.what() << "\n";
				}

				break;
			}
			case 2: {
				try {
					if (clienti.get_nr_abonati() == 0)
						std::cout << "Nu exista abonati!\n";
					else
						clienti.afisare();
				}
				catch (Exceptie<std::string>& e) {
					std::cout << e.what() << "\n";
				}
				break;
			}
			case 3: {
				try {
					std::cout << "\n" << "1.Abonamente Total" << '\n' << "2.Abonamente Premium" << '\n';
					int optiune2;
					std::cin >> optiune2;
					if (optiune2 == 1)
						std::cout << "\n" << "Numar total de abonamente: " << clienti.numar_abonati_premium<Abonament>() << "\n\n";
					else if (optiune2 == 2)
						std::cout << "\n" << "Numar abonamente premium : " << clienti.numar_abonati_premium<Abonament_Premium>() << "\n\n";
					else std::cout << "Optiune invalida!\n";

				}
				catch (Exceptie<std::string>& e) {
					std::cout << e.what() << "\n";
				}
				break;
			}
			case 4: {
				try {
					std::cout << "\n" << "Suma totala incasata : " << suma_totala<int>(clienti) << "\n\n";
				}

				catch (Exceptie<std::string>& e) {
					std::cout << e.what() << "\n";
				}
				break;
			}
			case 5: {
				loop = 0;
				break;
			}
			case 6: {
				system("cls");
			}
			}

		}
		catch (OptiuneInvalida<std::string>& e) {
			std::cout << e.what() << "\n";
		}
		catch (std::exception& e) {
			std::cout << e.what() << "\n";
		}
		catch (...) {
			std::cout << "Eroare necunoscuta\n";
		}

	}
	return 0;
}