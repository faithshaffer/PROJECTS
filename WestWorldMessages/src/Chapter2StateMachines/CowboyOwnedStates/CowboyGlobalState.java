package Chapter2StateMachines.CowboyOwnedStates;

import common.Messaging.Telegram;
import Chapter2StateMachines.Cowboy;
import Chapter2StateMachines.State;
import Chapter2StateMachines.MinersWifeOwnedStates.WifesGlobalState;

import static common.misc.utils.*;
import static common.misc.ConsoleUtils.*;
import static common.Time.CrudeTimer.*;
import static common.windows.*;
import static Chapter2StateMachines.MessageTypes.*;
import static Chapter2StateMachines.EntityNames.*;

public class CowboyGlobalState extends State<Cowboy> {

    static final CowboyGlobalState instance = new CowboyGlobalState();

    private CowboyGlobalState() {
    }

     @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException("Cloning not allowed");
    }


    @Override
    public void Enter(Cowboy cowboy) {
    }

    @Override
    public void Execute(Cowboy cowboy) {
        if (RandFloat() < 0.1) {
            cowboy.GetFSM().ChangeState(DoGunfight.Instance());
        }
    }

    @Override
    public void Exit(Cowboy cowboy) {
    }

    @Override
public boolean OnMessage(Cowboy cowboy, Telegram msg) {
    switch (msg.Msg) {
        case Msg_Gunfight:
            cout("\nMessage handled by " + GetNameOfEntity(cowboy.ID()) + " at time: "
                    + Clock.GetCurrentTime());

            SetTextColor(FOREGROUND_RED | FOREGROUND_INTENSITY);

            cout("\n" + GetNameOfEntity(cowboy.ID())
                    + ": Draw, partner! It's gunfight time!");

            // Change cowboy's state to DoGunfight
            cowboy.GetFSM().ChangeState(DoGunfight.Instance());
            break;

        case Msg_HiHoneyImHome:
            cout("\nMessage handled by " + GetNameOfEntity(cowboy.ID()) + " at time: "
                    + Clock.GetCurrentTime());

            SetTextColor(FOREGROUND_GREEN | FOREGROUND_INTENSITY);

            cout("\n" + GetNameOfEntity(cowboy.ID())
                    + ": Hi honey. I'm home! What's for dinner?");

            // Change cowboy's state to DoCowboyWork 
            cowboy.GetFSM().ChangeState(DoCowboyWork.Instance());
            break;

        case Msg_StewReady:
            cout("\nMessage handled by " + GetNameOfEntity(cowboy.ID()) + " at time: "
                    + Clock.GetCurrentTime());

            SetTextColor(FOREGROUND_BLUE | FOREGROUND_INTENSITY);

            cout("\n" + GetNameOfEntity(cowboy.ID())
                    + ": Mmm, stew is ready. Time to eat!");

            // Change cowboy's state to DoEatStew 
            cowboy.GetFSM().ChangeState(DoEatStew.Instance());
            break;
    }
            return true;
}
      public static CowboyGlobalState Instance() {
            return instance;
    }
}






