package Chapter2StateMachines.CowboyOwnedStates;

import common.Messaging.Telegram;
import Chapter2StateMachines.Cowboy;
import Chapter2StateMachines.State;
import static common.misc.utils.*;
import static common.misc.ConsoleUtils.*;
import static Chapter2StateMachines.MessageTypes.*;
import static Chapter2StateMachines.EntityNames.*;

public class DoEatStew extends State<Cowboy> {

    static final DoEatStew instance = new DoEatStew();

    private DoEatStew() {
    }

    @Override
    protected Object clone() throws CloneNotSupportedException {
        throw new CloneNotSupportedException("Cloning not allowed");
    }

    public static DoEatStew Instance() {
        return instance;
    }

    @Override
    public void Enter(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Time to eat some delicious stew!");
    }

    @Override
    public void Execute(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Eating stew... Yum Yum!");
        // You can add more logic for eating stew if needed.
    }

    @Override
    public void Exit(Cowboy cowboy) {
        cout("\n" + GetNameOfEntity(cowboy.ID()) + ": Finished eating stew.");
    }

    @Override
    public boolean OnMessage(Cowboy cowboy, Telegram msg) {
        return false;
    }
}
