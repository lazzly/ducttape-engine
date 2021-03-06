#include "Root.hpp"
#include "event/Timer.hpp"
#include "game/Game.hpp"

class CustomGame : public dt::Game, public dt::EventListener {
public:
    void OnInitialize() {
        mTimer1Count = 0;
        mTimer2Count = 0;

        std::cout << "TIMER: Starting 2 timers:" << std::endl;
        std::cout << "  1 - Event mode  - 1000ms" << std::endl;
        std::cout << "  2 - Thread mode - 2010ms" << std::endl;

        mTimer1 = new dt::Timer("Timer 1 (event mode)", 1000, true, false);
        mTimer2 = new dt::Timer("Timer 2 (thread mode)", 2010, true, true);

        dt::Root::get_mutable_instance().GetEventManager()->AddListener(this);

        mTotalTime = 0;
    }

    void HandleEvent(dt::Event* e) {
        if(e->GetType() == "DT_TIMERTICKEVENT") {
            dt::TimerTickEvent* t = (dt::TimerTickEvent*)e;
            bool t1 = (t->GetMessage() == "Timer 1 (event mode)");

            if(t1) {
                mTimer1Count++;
                std::cout << "Timer tick " << mTimer1Count << ": " << t->GetMessage() << std::endl;
            } else {
                mTimer2Count++;
                std::cout << "Timer tick " << mTimer2Count << ": " << t->GetMessage() << std::endl;
            }
        } else if(e->GetType() == "DT_BEGINFRAMEEVENT") {
            mTotalTime += ((dt::BeginFrameEvent*)e)->GetFrameTime();

            if(mTotalTime >= 10000) {
                RequestShutdown();
            }
        }
    }

public:
    dt::Timer* mTimer1;
    dt::Timer* mTimer2;
    int mTimer1Count;
    int mTimer2Count;

    int mTotalTime;
};

int main() {
    CustomGame game;
    game.Run();

    // we expect to have at least 9 ticks of timer 1 and 4 ticks of timer 2 within 10 seconds
    if(game.mTimer1Count < 9) {
        std::cerr << "Timer1 (event) did not tick often enough (only " << game.mTimer1Count << " times)." << std::endl;
        return 1;
    }

    if(game.mTimer2Count < 4) {
        std::cerr << "Timer2 (thread) did not tick often enough (only " << game.mTimer1Count << " times)." << std::endl;
        return 1;
    }

    std::cout << "Timers test finished." << std::endl;
    std::cout << "TIMERS: OK." << std::endl;

    return 0;
}
