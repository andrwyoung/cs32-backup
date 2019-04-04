class Concern
{
	std::string m_person;

public:
	//no default constructor
	Concern(std::string person)
		:m_person(person)
	{
	}
	virtual ~Concern()
	{
	}

    std::string person() const
	{
		return m_person;
	}

	virtual bool possibleFelony() const
	{
		return false;
	}

    virtual std::string description() const = 0;
};

class EthicsMatter : public Concern
{
public:
	EthicsMatter(std::string person)
		:Concern(person)
	{
	}

	~EthicsMatter()
	{
		std::cout << "Destroying " << person() << "'s ethics matter\n";
	}

    std::string description() const
	{
		return "An ethics matter";
	}
};

class HushPayment : public Concern
{
	int m_amount;

public:
	HushPayment(std::string person, int amount)
		:Concern(person), m_amount(amount)
	{
	}

	~HushPayment()
	{
		std::cout << "Destroying " << person() << "'s hush payment\n";
	}

    std::string description() const
	{
        std::string answer = "A $" + std::to_string(m_amount) + " payment";
        return answer;
	}
};

class Investigation : public Concern
{
public:
	Investigation(std::string person)
		:Concern(person)
	{
	}

	~Investigation()
	{
		std::cout << "Destroying " << person() << "'s investigation\n";
	}

	bool possibleFelony() const
	{
		return true;
	}

    std::string description() const
	{
		return "An investigation";
	}
};

