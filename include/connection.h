#ifndef CONNECTION_H_
#define CONNECTION_H_

class Connection
{
public:
  Connection(double weight = 0.0);
  void AdaptWeight(double delta);
  double GetWeight() const;
  double GetOldWeight() const;

private:
  double m_weight;
  double m_oldWeight;
};

#endif
