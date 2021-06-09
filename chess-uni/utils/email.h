#pragma once

using namespace System;
using namespace System::Net::Mail;
using System::Net::NetworkCredential;

auto
EMAIL_ADDR = gcnew String("Someone@domain.topleveldomain"),
EMAIL_PASS = gcnew String("whatever");
auto EMAIL_PORT = 587;

void SendEmail(String^ _subject, String^ _body, MailAddress^ _from, MailAddress^ _to) {
	auto mailClient = gcnew SmtpClient("smtp.gmail.com");
	mailClient->Port = EMAIL_PORT;
	mailClient->Credentials = gcnew NetworkCredential(EMAIL_ADDR, EMAIL_PASS);
	mailClient->EnableSsl = true;

	auto msgMail = gcnew MailMessage();
	msgMail->From = _from;
	msgMail->To->Add(_to);

	msgMail->Subject = _subject;
	msgMail->Body = _body;
	msgMail->IsBodyHtml = true;

	mailClient->Send(msgMail);
	msgMail->Dispose();
}

// USAGE:
//auto
//	from = gcnew MailAddress(L"Someone@domain.topleveldomain"),
//	to = gcnew MailAddress(L"Someone@domain.topleveldomain");

//auto
//	title = gcnew String("ahval porsi"),
//	body = gcnew String("salam chetory?");

//SendEmail(title, body, from, to, cc, bcc);
