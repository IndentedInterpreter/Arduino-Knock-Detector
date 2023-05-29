import time

event_pattern = [True, True, False, False, True]


def check_event():
    # Replace this with your own logic to check if the event occurred
    # For demonstration purposes, let's assume the event occurs randomly
    import random
    return random.choice([True, False])


def check_event_for_second():
    start_time = time.time()
    event_occurred = False
    x = 0
    while time.time() - start_time < 1:
        x += 1
        if check_event():
            print("Iterations:", x, "Time spent:", time.time() - start_time, "\n")
            event_occurred = True
            time.sleep(1 - (time.time() - start_time))  # Sleeps for the remainder of the time
            break

    return event_occurred

# Example usage
event_list = []

while True:
    event_happened = check_event_for_second()
    print("Event happened:", event_happened)
    if event_happened:
        event_count = 0
        while event_count < len(event_pattern):
            is_check_event = check_event_for_second()
            print("Check Event happened:", is_check_event)
            if is_check_event:
                event_list.append(is_check_event)
                event_count += 1

        print("Event list:", event_list)
        if event_list == event_pattern:
            print("Pattern matches!")
        else:
            print("Pattern doesn't match!")
        exit()
