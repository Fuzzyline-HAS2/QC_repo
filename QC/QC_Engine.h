#ifndef QC_ENGINE_H
#define QC_ENGINE_H

#include "QC_Types.h"
#include <vector>

class QCEngine {
private:
  std::vector<IQCRule *> fastRules;
  std::vector<IQCRule *> slowRules;
  unsigned long lastSlowCheckTime;
  unsigned long slowCheckInterval;

  QCEngine() : lastSlowCheckTime(0), slowCheckInterval(1000) {}

public:
  static QCEngine &getInstance() {
    static QCEngine instance;
    return instance;
  }

  QCEngine(const QCEngine &) = delete;
  void operator=(const QCEngine &) = delete;

  void begin(unsigned long intervalMs = 1000) {
    slowCheckInterval = intervalMs;
    Serial.println("[QC] Engine Initialized. Slow Check Interval: " +
                   String(slowCheckInterval) + "ms");
  }

  void addRule(IQCRule *rule) {
    if (rule->isFastCheck()) {
      fastRules.push_back(rule);
    } else {
      slowRules.push_back(rule);
    }
    Serial.println("[QC] Rule Added: " + rule->getId() + " (" +
                   rule->getName() + ")");
  }

  void tick() {
    for (auto rule : fastRules) {
      QCResult result = rule->check();
      if (result.isIssue()) {
        processResult(result);
      }
    }
    if (millis() - lastSlowCheckTime >= slowCheckInterval) {
      lastSlowCheckTime = millis();
      for (auto rule : slowRules) {
        QCResult result = rule->check();
        if (result.isIssue()) {
          processResult(result);
        }
      }
    }
  }

  void processResult(const QCResult &result) {
    Serial.println(result.toString());
  }
};

#endif // QC_ENGINE_H
