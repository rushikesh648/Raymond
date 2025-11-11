# The value 3 is read from a configuration variable
MAX_ATTEMPTS = config.get('LOGIN_MAX_ATTEMPTS', 3) 

def check_login_attempts(attempts):
    if attempts >= MAX_ATTEMPTS:
        print("Account locked. Too many attempts.")
        return False
    else:
        print(f"Attempts remaining: {MAX_ATTEMPTS - attempts}")
        return True

# To change the limit to 5, you only need to update the configuration setting.
