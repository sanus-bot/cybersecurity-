import re

def check_password_strength(password):
    if len(password) < 8:
        return False, "Password must be at least 8 characters long."
    if not re.search(r"[A-Z]", password):
        return False, "Password must contain at least one uppercase letter."
    if not re.search(r"[a-z]", password):
        return False, "Password must contain at least one lowercase letter."
    if not re.search(r"\d", password):
        return False, "Password must contain at least one digit."
    if not re.search(r"[!@#$%^&*(),.?\":{}|<>]", password):
        return False, "Password must contain at least one special character."
    return True, "Password is strong."

def main():
    password = input("Enter your password: ")
    is_strong, message = check_password_strength(password)
    if is_strong:
        print("Your password is strong.")
    else:
        print(f"Your password is not strong enough: {message}")

if _name_ == "_main_":
    main()