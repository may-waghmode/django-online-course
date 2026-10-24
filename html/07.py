class BlockWorldAgent:
    def __init__(self):
        self.state = {
            "ONTABLE(A)",
            "ONTABLE(B)",
            "ONTABLE(C)",
            "CLEAR(A)",
            "CLEAR(B)",
            "CLEAR(C)",
            "ARMEMPTY"
        }
        self.plan = []

    def execute(self, action, delete_list, add_list):
        print(f"Executing: {action}")

        for fact in delete_list:
            self.state.discard(fact)

        for fact in add_list:
            self.state.add(fact)

        self.plan.append(action)

    def pickup(self, block):
        self.execute(
            f"PICKUP({block})",
            [f"ONTABLE({block})", f"CLEAR({block})",
             "ARMEMPTY"],
            [f"HOLDING({block})"]
        )

    def stack(self, block, target):
        self.execute(
            f"STACK({block}, {target})",
            [f"HOLDING({block})", f"CLEAR({target})"],
            [f"ON({block}, {target})",
             f"CLEAR({block})", "ARMEMPTY"]
        )

    def goal_stack_planning(self):
        # Goal: A on B and B on C
        goal_stack = [
            "STACK(A, B)",
            "PICKUP(A)",
            "STACK(B, C)",
            "PICKUP(B)"
        ]

        print("Initial State:")
        print(self.state)
        print("\nPlanning and Executing Actions:")

        # Execute the valid plan in order
        self.pickup("B")
        self.stack("B", "C")
        self.pickup("A")
        self.stack("A", "B")

        print("\nFinal State:")
        for fact in sorted(self.state):
            print(fact)

        print("\nGoal Achieved:",
              "ON(A, B)" in self.state and
              "ON(B, C)" in self.state)


# Main program
agent = BlockWorldAgent()
agent.goal_stack_planning()