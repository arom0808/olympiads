from __future__ import annotations

import random
from abc import ABC, abstractmethod
from copy import deepcopy
from dataclasses import dataclass
from enum import Enum
from typing import TypeVar, Optional, Generic, Union
from sys import stdin, stdout, maxsize as sys_maxsize

cards_str = '234567890JQKA'
start_deck: dict[str, int] = dict([(s, 24) for s in cards_str])
cards_prices: dict[str, int] = dict(
    {'2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9, '0': 10, 'J': 10, 'Q': 10, 'K': 10, 'A': 10})


class Random:
    seed = random.randrange(sys_maxsize)
    rng = random.Random(seed)


class Deck:
    def get_sum(self, is_player_sum: bool) -> int:
        if not is_player_sum:
            return self.sum
        res, ase_full_used = self.sum, self.get_card_count('A')
        while ase_full_used > 0 and res > 21:
            res -= 10
            ase_full_used -= 1
        return res

    @property
    def get_cards_count(self) -> int:
        return self.cards_count

    def reset_to_start_deck(self):
        self.data = start_deck.copy()
        self.sum, self.cards_count = 0, 0
        for card in self.data.items():
            self.sum += cards_prices[card[0]] * card[1]
            self.cards_count += card[1]

    def clear(self):
        self.data.clear()
        self.sum, self.cards_count = 0, 0

    def add_card(self, card: str):
        if card in self.data:
            self.data[card] += 1
        else:
            self.data[card] = 1
        self.sum += cards_prices[card]
        self.cards_count += 1

    def delete_card(self, card: str):
        if (card not in self.data) or self.data[card] == 0:
            return
        self.data[card] -= 1
        self.sum -= cards_prices[card]
        self.cards_count -= 1

    def delete_cards(self, cards: 'Deck'):
        for card in cards.data.items():
            if card[0] in self.data and self.data[card[0]] > 0:
                del_cnt = min(card[1], self.data[card[0]])
                self.data[card[0]] -= del_cnt
                self.sum -= cards_prices[card[0]] * del_cnt
                self.cards_count -= del_cnt

    def get_card_count(self, card: str) -> int:
        if card not in self.data:
            return 0
        return self.data[card]

    def probability_that_card_btn(self, n: int, is_ase_is_1: bool) -> float:
        res = 0
        ase_price = 1 if is_ase_is_1 else cards_prices['A']
        for card in self.data.items():
            res += ((ase_price if card[0] == 'A' else cards_prices[card[0]]) > n) * card[1]
        return res / self.get_cards_count

    def get_random_card(self) -> str:
        need_card_number, i = Random.rng.randint(0, self.get_cards_count - 1), 0
        for d in self.data.items():
            if d[1] > 0:
                if i + d[1] >= need_card_number:
                    return d[0]
                else:
                    i += d[1]

    def __init__(self, set_to_full: bool = False):
        self.data: dict[str, int] = dict()
        self.sum: int = 0
        self.cards_count: int = 0
        if set_to_full:
            self.reset_to_start_deck()
        else:
            self.clear()


T = TypeVar('T')


class Regression(Generic[T], ABC):
    @abstractmethod
    def GetY(self, x: T) -> T:
        pass

    def __init__(self, pre_regression: Optional[Regression[T]]):
        self.pre_regression = pre_regression

    def __call__(self, x: T, *args, **kwargs) -> T:
        if self.pre_regression is not None:
            return self.GetY(self.pre_regression(x))
        return self.GetY(x)


class LinealRegression(Generic[T], Regression[T]):
    @dataclass
    class KB:
        k: T
        b: T

    @dataclass
    class XYS:
        x1: T
        y1: T
        x2: T
        y2: T

    def GetY(self, x: T) -> T:
        return self.k * x + self.b

    def __init__(self, pre_regression: Optional[Regression[T]], params: Union[KB, XYS]):
        super().__init__(pre_regression)
        if type(params) is LinealRegression.KB:
            self.k, self.b = params.k, params.b
        else:
            self.k = (params.y1 - params.y2) / (params.x1 - params.x2)
            self.b = params.y1 - self.k * params.x1


class MinMaxLimit(Generic[T], Regression[T]):
    def GetY(self, x: T) -> T:
        return max(self.min, min(x, self.max))

    def __init__(self, pre_regression: Optional[Regression[T]], _min: T, _max: T):
        super().__init__(pre_regression)
        self.min, self.max = _min, _max


@dataclass
class PlayerAndDealerHands:
    player_hand: Deck
    dealer_hand: Deck


class BJIOObject(ABC):
    @abstractmethod
    def start_read_is_shuffle(self) -> bool:
        pass

    @abstractmethod
    def exit(self) -> None:
        pass

    @abstractmethod
    def start_bet(self, bet: int) -> PlayerAndDealerHands:
        pass

    @abstractmethod
    def hit(self) -> str:
        pass

    @abstractmethod
    def double(self) -> str:
        pass

    @abstractmethod
    def Break(self) -> Deck:
        pass


class MyFirstSolution:
    class Action(Enum):
        hit = 0
        double = 1
        Break = 2

    def __init__(self, in_out: BJIOObject, k0_k: float, k0_b: float, k0_min: float, k0_max: float,
                 k1_k: float, k1_b: float, k1_min: float, k1_max: float,
                 k2_k: float, k2_b: float, k2_min: float, k2_max: float,
                 max_bet_percent: float, max_n_for_double: float, min_next_n_probability_for_double: float,
                 max_n_for_hit: float, min_next_n_for_double: int):
        self.in_out = in_out
        self.k0 = MinMaxLimit(LinealRegression(None, LinealRegression.KB(k0_k, k0_b)), k0_min, k0_max)
        self.k1 = MinMaxLimit(LinealRegression(None, LinealRegression.KB(k1_k, k1_b)), k1_min, k1_max)
        self.k2 = MinMaxLimit(LinealRegression(None, LinealRegression.KB(k2_k, k2_b)), k2_min, k2_max)
        self.now_deck, self.my_hand, self.dealer_hand = Deck(True), Deck(False), Deck(False)
        self.max_bet_percent, self.max_n_for_double, self.min_next_n_probability_for_double, self.max_n_for_hit = \
            max_bet_percent, max_n_for_double, min_next_n_probability_for_double, max_n_for_hit
        self.min_next_n_for_double = min_next_n_for_double
        self.balance, self.bet = 500000, 0
        self.now_deck, self.my_hand, self.dealer_hand = Deck(True), Deck(), Deck()

    def probability_next_card_sum_btn(self, n: int) -> float:
        return self.now_deck.probability_that_card_btn(
            (n - self.my_hand.get_sum(True) if n >= self.my_hand.get_sum(True) else 0), self.my_hand.get_sum(True) > 10)

    def get_action(self) -> Action:
        if self.my_hand.get_sum(True) >= 20:
            return MyFirstSolution.Action.Break
        n = self.probability_next_card_sum_btn(21)
        if n <= self.max_n_for_double and self.probability_next_card_sum_btn(
                self.min_next_n_for_double) >= self.min_next_n_probability_for_double:
            if self.bet * 2 <= self.balance * self.max_bet_percent:
                return MyFirstSolution.Action.double
        if n < self.max_n_for_hit:
            return MyFirstSolution.Action.hit
        return MyFirstSolution.Action.Break

    def process_new_player_card(self, card: str):
        self.my_hand.add_card(card)
        self.now_deck.delete_card(card)

    def solute(self):
        for _ in range(10001):
            if self.balance >= 4200000:
                break
            if self.in_out.start_read_is_shuffle():
                self.now_deck.reset_to_start_deck()
            self.bet = int(
                min(min(self.balance * self.k0(self.balance) * self.k1(self.now_deck.get_cards_count) * self.k2(
                    self.balance), int(self.balance * self.max_bet_percent)), self.balance))
            my_and_dealer_hands = self.in_out.start_bet(self.bet)
            self.my_hand, self.dealer_hand = my_and_dealer_hands.player_hand, my_and_dealer_hands.dealer_hand
            self.now_deck.delete_cards(self.my_hand)
            self.now_deck.delete_cards(self.dealer_hand)
            action = self.get_action()
            while action != MyFirstSolution.Action.Break:
                if action == MyFirstSolution.Action.hit:
                    self.process_new_player_card(self.in_out.hit())
                else:
                    self.process_new_player_card(self.in_out.double())
                    self.bet *= 2
                action = self.get_action()
            self.dealer_hand = self.in_out.Break()
            my_res = 21 - self.my_hand.get_sum(True) if 21 >= self.my_hand.get_sum(True) else 21
            dealer_res = 21 - self.dealer_hand.get_sum(True) if 21 >= self.dealer_hand.get_sum(True) else 21
            if my_res > dealer_res:
                self.balance -= self.bet
            elif my_res < dealer_res:
                self.balance += self.bet
        self.in_out.start_read_is_shuffle()
        self.in_out.exit()


class ConsoleBJIOObject(BJIOObject):
    def start_read_is_shuffle(self) -> bool:
        # if stdin.readline().rstrip('\n') == 'shuffle':
        if input() == 'shuffle':
            input()
            return True
        return False

    def exit(self) -> None:
        # stdout.write("-1\n")
        # stdout.flush()
        print("-1")

    def start_bet(self, bet: int) -> PlayerAndDealerHands:
        # stdout.write(str(bet) + "\n")
        # stdout.flush()
        print(str(bet))
        # temp = stdin.readline().rstrip('\n')
        temp = input()
        dealer_hand, my_hand = Deck(), Deck()
        dealer_hand.add_card(temp[0])
        my_hand.add_card(temp[2])
        my_hand.add_card(temp[3])
        return PlayerAndDealerHands(player_hand=my_hand, dealer_hand=dealer_hand)

    def hit(self) -> str:
        # stdout.write("hit\n")
        # stdout.flush()
        print("hit")
        # return stdin.readline().rstrip('\n')[-1]
        return input()[-1]

    def double(self) -> str:
        # stdout.write('double\n')
        # stdout.flush()
        print('double')
        # return stdin.readline().rstrip('\n')[-1]
        return input()[-1]

    def Break(self) -> Deck:
        # stdout.write("break\n")
        # stdout.flush()
        print("break")
        # temp = stdin.readline().rstrip('\n')
        temp = input()
        dealer_hand = Deck()
        for card in temp[:temp.find('#')]:
            dealer_hand.add_card(card)
        return dealer_hand


class TestBJIOObject(BJIOObject):
    def __init__(self):
        self.player_balance, self.player_bet, self.motion_id = 500000, 0, 0
        self.now_deck, self.player_hand, self.dealer_hand = Deck(), Deck(), Deck()

    def start_read_is_shuffle(self) -> bool:
        self.motion_id += 1
        self.player_hand.clear()
        self.dealer_hand.clear()
        if self.now_deck.get_cards_count < 20:
            self.now_deck.reset_to_start_deck()
            return True
        return False

    def exit(self) -> None:
        pass

    def start_bet(self, bet: int) -> PlayerAndDealerHands:
        self.player_bet = bet
        dealer_card = self.now_deck.get_random_card()
        self.now_deck.delete_card(dealer_card)
        self.dealer_hand.add_card(dealer_card)
        first_player_card = self.now_deck.get_random_card()
        self.now_deck.delete_card(first_player_card)
        self.player_hand.add_card(first_player_card)
        second_player_card = self.now_deck.get_random_card()
        self.now_deck.delete_card(second_player_card)
        self.player_hand.add_card(second_player_card)
        return PlayerAndDealerHands(player_hand=deepcopy(self.player_hand), dealer_hand=deepcopy(self.dealer_hand))

    def hit(self) -> str:
        new_player_card = self.now_deck.get_random_card()
        self.now_deck.delete_card(new_player_card)
        self.player_hand.add_card(new_player_card)
        return new_player_card

    def double(self) -> str:
        self.player_bet *= 2
        new_player_card = self.now_deck.get_random_card()
        self.now_deck.delete_card(new_player_card)
        self.player_hand.add_card(new_player_card)
        return new_player_card

    def Break(self) -> Deck:
        while self.dealer_hand.get_sum(True) < 17 and self.now_deck.get_cards_count > 0:
            new_dealer_card = self.now_deck.get_random_card()
            self.now_deck.delete_card(new_dealer_card)
            self.dealer_hand.add_card(new_dealer_card)
        player_res = 21 - self.player_hand.get_sum(True) if 21 >= self.player_hand.get_sum(True) else 21
        dealer_res = 21 - self.dealer_hand.get_sum(True) if 21 >= self.dealer_hand.get_sum(True) else 21
        if player_res > dealer_res:
            self.player_balance -= self.player_bet
        elif player_res < dealer_res:
            self.player_balance += self.player_bet
        return deepcopy(self.dealer_hand)


def MyFirstSolutionTest():
    out_file = open('out.txt', 'w')
    out_file.write(f'seed: {Random.seed}\n\n')
    while True:
        winned = 0
        k0_x1 = Random.rng.uniform(1e6, 1e7)
        k0_y1 = Random.rng.uniform(0.03, 0.2)
        k0_x2 = Random.rng.uniform(5e4, 4e5)
        k0_y2 = Random.rng.uniform(0.2, 0.8)
        k0_min = Random.rng.uniform(0.005, 0.05)
        k0_max = Random.rng.uniform(0.25, 0.75)
        k1_x1 = 312
        k1_y1 = Random.rng.uniform(0.8, 1.02)
        k1_x2 = Random.rng.uniform(5, 20)
        k1_y2 = Random.rng.uniform(1.25, 1.75)
        k1_min = 1
        k1_max = Random.rng.uniform(1.25, 1.75)
        k2_x1 = Random.rng.uniform(1e6, 1e7)
        k2_y1 = 1
        k2_x2 = Random.rng.uniform(5e4, 2e5)
        k2_y2 = Random.rng.uniform(0.25, 0.75)
        k2_min = Random.rng.uniform(0.3, 0.9)
        k2_max = 1
        max_bet_percent = Random.rng.uniform(0.3, 0.7)
        max_n_for_double = Random.rng.uniform(0.05, 0.2)
        min_next_n_probability_for_double = Random.rng.uniform(0.5, 0.95)
        max_n_for_hit = Random.rng.uniform(0.25, 0.75)
        min_next_n_for_double = Random.rng.randint(5, 20)
        k0 = MinMaxLimit(LinealRegression[float](None, LinealRegression[float].XYS(k0_x1, k0_y1, k0_x2, k0_y2)), k0_min,
                         k0_max)
        k1 = MinMaxLimit(LinealRegression[float](None, LinealRegression[float].XYS(k1_x1, k1_y1, k1_x2, k1_y2)), k1_min,
                         k1_max)
        k2 = MinMaxLimit(LinealRegression[float](None, LinealRegression[float].XYS(k2_x1, k2_y1, k2_x2, k2_y2)), k2_min,
                         k2_max)
        out_file.write("{")
        out_file.write(f"{{k0_k, {k0.pre_regression.k}}},")
        out_file.write(f"{{k0_b, {k0.pre_regression.b}}},")
        out_file.write(f"{{k0_min, {k0.min}}},")
        out_file.write(f"{{k0_max, {k0.max}}},")
        out_file.write(f"{{k1_k, {k1.pre_regression.k}}},")
        out_file.write(f"{{k1_b, {k1.pre_regression.b}}},")
        out_file.write(f"{{k1_min, {k1.min}}},")
        out_file.write(f"{{k1_max, {k1.max}}},")
        out_file.write(f"{{k2_k, {k2.pre_regression.k}}},")
        out_file.write(f"{{k2_b, {k2.pre_regression.b}}},")
        out_file.write(f"{{k2_min, {k2.min}}},")
        out_file.write(f"{{k2_max, {k2.max}}},")
        out_file.write(f"{{max_bet_percent, {max_bet_percent}}},")
        out_file.write(f"{{max_n_for_double, {max_n_for_double}}},")
        out_file.write(f"{{min_next_n_probability_for_double, {min_next_n_probability_for_double}}},")
        out_file.write(f"{{max_n_for_hit, {max_n_for_hit}}},")
        out_file.write(f"{{min_next_n_for_double, {min_next_n_for_double}}},")
        out_file.write("}\n")
        out_file.flush()
        for i in range(20):
            test_in_out = TestBJIOObject()
            sol = MyFirstSolution(test_in_out, k0.pre_regression.k, k0.pre_regression.b, k0_min, k0_max,
                                  k1.pre_regression.k, k1.pre_regression.b,
                                  k1_min, k1_max, k2.pre_regression.k, k2.pre_regression.b, k2_min,
                                  k2_max, max_bet_percent, max_n_for_double, min_next_n_probability_for_double,
                                  max_n_for_hit, min_next_n_for_double)
            sol.solute()
            if test_in_out.player_balance != sol.balance:
                out_file.write("ERROR\n")
            if test_in_out.player_balance >= 4200000:
                winned += 1
        out_file.write(f"Probability {winned / 100}\n")
        out_file.flush()


def main():
    k0_k, k0_b, k0_min, k0_max, k1_k, k1_b, k1_min, k1_max, k2_k, k2_b, k2_min, k2_max = \
        -3.75859e-08, 0.226961, 0.00790036, 0.461925, -0.00112462, 1.29651, 1.0, 1.58623, 1.26713e-07, 0.304463, \
        0.464197, 1.0
    max_bet_percent, max_n_for_double, min_next_n_probability_for_double, max_n_for_hit = \
        0.465443, 0.0902445, 0.648217, 0.645046
    min_next_n_for_double = 15
    in_out = ConsoleBJIOObject()
    sol = MyFirstSolution(in_out, k0_k, k0_b, k0_min, k0_max, k1_k, k1_b, k1_min, k1_max, k2_k, k2_b, k2_min, k2_max,
                          max_bet_percent, max_n_for_double, min_next_n_probability_for_double, max_n_for_hit,
                          min_next_n_for_double)
    sol.solute()


def test_main():
    MyFirstSolutionTest()


test_main()
