def check_login_attempts(attempts):
    # The value 3 is hardcoded here
    MAX_ATTEMPTS = 3
    if attempts >= MAX_ATTEMPTS:
        print("Account locked. Too many attempts.")
        return False
    else:
        print(f"Attempts remaining: {MAX_ATTIPTS - attempts}")
        return True

# If you ever need to change the limit to 5, you MUST edit and recompile the code.
