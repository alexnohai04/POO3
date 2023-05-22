template <typename T>
class Exceptie : public std::exception {
public:
	virtual const char* what() const noexcept override {
		return "Exista o eroare!";
	}
};

template <typename T>
class CnpInvalid : public Exceptie<T> {
public:
	virtual const char* what() const noexcept override {
		return "CNP invalid";
	}
};

template <typename T>
class NumarTelefonInvalid : public Exceptie<T> {
public:
	virtual const char* what() const noexcept override {
		return "Numar de telefon invalid";
	}
};

template <typename T>
class OptiuneInvalida : public Exceptie<T> {
public:
	virtual const char* what() const noexcept override {
		return "Optiune invalida";
	}
};

class connection {
private:
	bool opened = false;
public:
	void open() { opened = true; }
	bool free() const { return !opened; }
	void close() { opened = false; }
	~connection() { close(); }
};

class connection_pool {
private:
	static const int max_conns = 3;
	std::vector<connection> conns{ max_conns };
public:
	connection& get_conn() {
		for (auto& conn : conns)
			if (conn.free()) {
				conn.open();
				return conn;
			}
		throw std::runtime_error("\nAti atins limita de 3 abonati!\n");
	}
};

class Abonament {
public:
	Abonament() {/* cout << "Constructor Default Abonament\n";*/ }
	~Abonament() { /*cout << "Destructor Default Abonament\n";*/ }
	Abonament(std::string _nume_abonament, float _pret, int _perioada) {
		//cout << "Constructor cu parametru Abonament\n";
		nume_abonament = _nume_abonament;
		pret = _pret;
		perioada = _perioada;
	}
	Abonament(const Abonament& a) {
		nume_abonament = a.nume_abonament;
		pret = a.pret;
		perioada = a.perioada;
		//cout << "Constructor de copiere Abonament\n";
	}
	//supraincarcarea operatorului =
	Abonament& operator=(const Abonament& a) {
		nume_abonament = a.nume_abonament;
		pret = a.pret;
		perioada = a.perioada;
		return *this;
	}
	//getter nume
	std::string get_nume_abonament() {
		return nume_abonament;
	}
	//getter pret
	float get_pret() {
		return pret;
	}
	//getter perioada
	int get_perioada() {
		return perioada;
	}

	//setter  nume
	void set_nume_abonament(std::string _nume_abonament) {
		nume_abonament = _nume_abonament;
	}
	//setter pret
	void set_pret(float _pret) {
		pret = _pret;
	}
	//setter perioada
	void set_perioada(int _perioada) {
		perioada = _perioada;
	}
	//functie virtuala 
	virtual void afisare();
	//functie virtuala 
	virtual void citire();
protected:
	std::string nume_abonament;
	float pret;
	int perioada;
};

class Abonament_Premium : public Abonament {
public:
	Abonament_Premium() { /*cout << "Constructor Default Abonament_Premium\n";*/ }
	~Abonament_Premium() { /*cout << "Destructor Default Abonament_Premium\n";*/ }
	//constructor cu parametrii
	Abonament_Premium(std::string _nume_abonament, float _pret, int _perioada, int _reducere) :Abonament(_nume_abonament, _pret, _perioada) {
		//cout << "Constructor cu parametru Abonament_Premium\n";
		reducere = _reducere;
	}
	Abonament_Premium(int _reducere, Abonament& a) :Abonament(a) {
		reducere = _reducere;
		//cout << "Constructor cu parametru Abonament_Premium\n";
	}
	//constructor de copiere
	Abonament_Premium(const Abonament_Premium& a) {
		reducere = a.reducere;
		//cout << "Constructor de copiere Abonament_Premium\n";
	}

	//supraincarcarea operatorului =
	Abonament_Premium& operator=(const Abonament_Premium& a) {
		Abonament::operator=(a);
		reducere = a.reducere;
		return *this;
	}

	//getter reducere
	int get_reducere() {
		return reducere;
	}
	//setter reducere
	void set_reducere(int _reducere) {
		reducere = _reducere;
	}
	//functie virtuala de afisare
	void afisare();
	//functie virtuala de citire
	void citire();

private:
	int reducere;
};

class Persoana {
public:
	Persoana() {/* cout << "Constructor Default Persoana\n";*/ }
	~Persoana() {/* cout << "Destructor Default Persoana\n";*/ }
	Persoana(int _id, std::string _nume, std::string _cnp) {
		//cout << "Constructor cu parametru Persoana\n";
		id = _id;
		nume = _nume;

		if (_cnp.length() != 13)
			throw Exceptie<std::string>();
		cnp = _cnp;
	}
	Persoana(const Persoana& p) {
		id = p.id;
		nume = p.nume;
		cnp = p.cnp;
		//cout << "Constructor de copiere Persoana\n";
	}
	//supraincarcarea operatorului =
	Persoana& operator=(const Persoana& p) {
		id = p.id;
		nume = p.nume;
		if (p.cnp.length() != 13)
			throw Exceptie<std::string>();
		cnp = p.cnp;
		return *this;
	}
	//getter id
	int get_id() {
		return id;
	}
	//getter nume
	std::string get_nume() {
		return nume;
	}
	//getter cnp
	std::string get_cnp() {
		return cnp;
	}
	//setter id
	void set_id(int _id) {
		id = _id;
	}
	//setter nume
	void set_nume(std::string _nume) {
		nume = _nume;
	}
	//setter cnp
	void set_cnp(std::string _cnp) {
		if (_cnp.length() != 13)
			throw Exceptie<std::string>();
		cnp = _cnp;
	}
	//functie virtuala de citire
	virtual void citire() = 0;
	//functie virtuala de afisare
	virtual void afisare();

private:
	int id;
	std::string nume;
	std::string cnp;
};

class Abonat : public Persoana {
public:
	Abonat() { /*cout << "Constructor Default Abonat\n";*/ }
	~Abonat() {/*cout << "Destructor Default Abonat\n"; */ }
	//constructor cu parametrii
	Abonat(std::string _nr_telefon, std::string _nume_abonament, float _pret, int _perioada, int _id, std::string _nume, std::string _cnp) :Persoana(_id, _nume, _cnp) {
		//cout << "Constructor cu parametru Abonat\n";
		nr_telefon = _nr_telefon;
		if (_nr_telefon.size() != 10)
			throw Exceptie<std::string>();
		x = new Abonament(_nume_abonament, _pret, _perioada);
	}
	Abonat(std::string _nr_telefon, std::string _nume_abonament, float _pret, int _perioada, Persoana& p) :Persoana(p) {
		//cout << "Constructor cu parametru Abonat\n";
		nr_telefon = _nr_telefon;
		if (_nr_telefon.size() != 10)
			throw Exceptie<std::string>();
		x = new Abonament(_nume_abonament, _pret, _perioada);
	}
	Abonat(std::string _nr_telefon, Abonament& a, Persoana& p) :Persoana(p) {
		//cout << "Constructor cu parametru Abonat\n";
		if (_nr_telefon.size() != 10)
			throw Exceptie<std::string>();
		nr_telefon = _nr_telefon;
		x = &a;
	}
	//constructor de copiere
	Abonat(const Abonat& a) :Persoana(a), x(a.x) {
		nr_telefon = a.nr_telefon;
		//cout << "Constructor de copiere Abonat\n";
	}
	//supraincarcarea operatorului =
	Abonat& operator=(const Abonat& a) {
		Persoana::operator=(a);
		nr_telefon = a.nr_telefon;
		x = a.x;
		return *this;
	}

	//getter nr_telefon	
	std::string getNrTelefon() const {
		return nr_telefon;
	}
	//getter abonament
	Abonament* getAbonament() {
		return x;
	}


	//setter
	void setNrTelefon(const std::string _nr_telefon) {

		if (_nr_telefon.size() != 10)
			throw Exceptie<std::string>();
		nr_telefon = _nr_telefon;
	}
	//setter abonament
	void setAbonament(Abonament* _x) {
		x = _x;
	}
	//functie virtuala de citire
	void citire();
	//functie virtuala de afisare
	void afisare();



protected:
	std::string nr_telefon;
	Abonament* x;
};

class Clienti {
public:
	static Clienti& getInstance() {
		static Clienti instance;
		return instance;
	}
	Clienti() { /*cout << "Constructor Default Clienti";*/ }
	~Clienti() {/* cout << "Destructor Default Clienti";*/ }
	//constructor cu parametrii
	Clienti(std::vector <std::shared_ptr<Abonat>> _client) {
		//cout << "Constructor cu parametru Clienti\n";
		client = _client;
	}
	//constructor de copiere
	Clienti(const Clienti& c) {
		client = c.client;
		//cout << "Constructor de copiere Clienti\n";
	}
	//getter
	std::vector <std::shared_ptr<Abonat>> getClient() {
		return client;
	}
	//functie de adaugare abonat
	void adaugaAbonat(Abonat& _Abonat) {
		client.push_back(std::make_unique<Abonat>(_Abonat));
	}
	//functie de stergere ultimul abonat
	void stergeAbonat() {
		client.pop_back();
	}
	//functie de afisare
	void afisare() {
		for (int i = 0; i < client.size(); i++) {
			std::cout << "\n============Abonatul " << i + 1 << "============\n";
			client[i]->afisare();
		}
		std::cout << "==================================\n";
	}
	int get_nr_abonati() {
		return client.size();
	}
	//getter pentru vectorul de clienti
	std::vector <std::shared_ptr<Abonat>> get_client() {
		return client;
	}


	template <typename AbonamentType>
	int numar_abonati_premium() {
		int numar = 0;
		for (int i = 0; i < client.size(); i++) {
			if (dynamic_cast<AbonamentType*>(client[i]->getAbonament())) {
				numar++;
			}
		}
		return numar;
	}

private:
	std::vector <std::shared_ptr<Abonat>>client;
};

//functie virtuala de citire
void Abonament::citire() {
	std::cout << "Nume Abonament: ";
	std::cin >> nume_abonament;
	std::cout << "Pret: ";
	std::cin >> pret;
	std::cout << "Perioada: ";
	std::cin >> perioada;
}
//functie virtuala de afisare
void Abonament::afisare() {
	std::cout << "Nume Abonament:" << nume_abonament << '\n';
	std::cout << "Pret:" << pret << '\n';
	std::cout << "Perioada:" << perioada << '\n';
}
void Abonament_Premium::afisare() {
	Abonament::afisare();
	std::cout << "Reducere:" << reducere << '\n';
}
//functie virtuala de citire
void Abonament_Premium::citire() {
	Abonament::citire();
	std::cout << "Reducere: ";
	std::cin >> reducere;
}
//functie virtuala de citire
void Persoana::citire() {
	std::cout << "Id: ";
	std::cin >> id;
	std::cout << "Nume: ";
	std::cin >> nume;
	std::cout << "CNP: ";
	std::cin >> cnp;
	if (cnp.size() != 13) {
		//cout << "CNP invalid\n";
		throw CnpInvalid<std::string>();
	}
}
//functie virtuala de afisare
void Persoana::afisare() {
	std::cout << "Id: " << id << "\n";
	std::cout << "Nume: " << nume << "\n";
	std::cout << "CNP: " << cnp << "\n";
}

void Abonat::citire() {
	Persoana::citire();
	std::cout << "Numar Telefon:\n";
	std::cin >> nr_telefon;
	if (nr_telefon.size() != 10) {
		throw NumarTelefonInvalid<std::string>();
	}
	std::cout << "Ce tip de abonament doriti sa adaugati?\n";
	std::cout << "1. Abonament Standard\n";
	std::cout << "2. Abonament Premium\n";
	int optiune;
	std::cin >> optiune;
	if (optiune != 1 && optiune != 2) {
		throw OptiuneInvalida<std::string>();
	}
	if (optiune == 1) {
		x = new Abonament();
	}
	else if (optiune == 2) {
		x = new Abonament_Premium();
	}
	else {
		throw Exceptie<std::string>();
	}
	x->citire();
	std::cout << "\n";

}
//functie  de afisare

void Abonat::afisare() {
	Persoana::afisare();
	std::cout << "Numar Telefon: " << nr_telefon << "\n";
	std::cout << "Abonament: ";
	x->afisare();
	std::cout << "\n";
}

template <typename T>
float suma_totala(Clienti& clienti = Clienti::getInstance()) {
	T suma = 0;
	for (int i = 0; i < clienti.get_client().size(); i++) {
		if (dynamic_cast<Abonament_Premium*>(clienti.get_client()[i]->getAbonament())) {
			Abonament_Premium* abonament_premium = dynamic_cast<Abonament_Premium*>(clienti.get_client()[i]->getAbonament());
			suma += ((abonament_premium->get_pret()) * (abonament_premium->get_perioada())) - (abonament_premium->get_reducere());
		}
		else {
			suma += (clienti.get_client()[i]->getAbonament()->get_pret()) * (clienti.get_client()[i]->getAbonament()->get_perioada());
		}
	}
	return suma;
}