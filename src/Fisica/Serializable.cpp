class Serializable
{
    public:
        Serializable();
        virtual ~Serializable();
        virtual string serializar();
        virtual bool hidratar(string serializado);
};
