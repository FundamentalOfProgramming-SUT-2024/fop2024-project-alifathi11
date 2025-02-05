import smtplib
from email.mime.text import MIMEText
from sys import exit

with open("email_data.txt", "r") as f:
    recipient_email = f.readline().strip()
    user_password = f.readline().strip()

sender_email = "rogue.fop@gmail.com"  
app_password = "guzx piig wvpl hcdg"  

subject = "Password Recovery"
body = f"Your password is: {user_password}"
msg = MIMEText(body)
msg["Subject"] = subject
msg["From"] = sender_email
msg["To"] = recipient_email


try:
    with smtplib.SMTP_SSL("smtp.gmail.com", 465) as server:
        server.login(sender_email, app_password)
        server.sendmail(sender_email, recipient_email, msg.as_string())
except Exception as e:
    exit(0)
