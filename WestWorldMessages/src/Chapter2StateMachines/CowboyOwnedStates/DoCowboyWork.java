package Chapter2StateMachines.CowboyOwnedStates;

import common.Messaging.Telegram;
import Chapter2StateMachines.Cowboy;
import Chapter2StateMachines.State;
import static common.misc.utils.*;
import static common.misc.ConsoleUtils.*;
import static Chapter2StateMachines.EntityNames.*;

public class DoCowboyWork extends State<Cowboy> {

    static final DoCowboyWork instance = new DoCowboyWork();

    private DoCowboyWork() {
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException("Cloning not allowed");
    }

    public static DoCowboyWork Instance() {
        return instance;
    }

    @Override
    public void Enter(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Time to do some cowboy work!");
    }

    @Override
    public void Execute(Cowboy cowboy) {
        switch (RandInt(0, 2)) {
            case 0:
                cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Lassoing some cattle");
                break;
            case 1:
                cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Riding the range");
                break;
            case 2:
                cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Fixing the fence");
                break;
        }
    }

    @Override
    public void Exit(Cowboy cowboy) {
    }

    @Override
    public boolean OnMessage(Cowboy cowboy, Telegram msg) {
        return false;
    }
}