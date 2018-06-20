# -*- coding: utf-8 -*-
# perl

use LWP::UserAgent;
use utf8;

binmode(STDIN, ':encoding(utf8)');
binmode(STDOUT, ':encoding(utf8)');
binmode(STDERR, ':encoding(utf8)');

my $ua = LWP::UserAgent->new;

my $CDR_endpoint = "https://home.oxygentw.net/tools/CDR.php?u=";
my $server_endpoint = "https://home.oxygentw.net/tools/CDR.php?u=https://opendata.cwb.gov.tw/api/v1/rest/datastore/O-A0001-001?Authorization=rdec-key-123-45678-011121314";
 
# set custom HTTP request header fields
my $req = HTTP::Request->new(GET => $server_endpoint);
$req->header('content-type' => 'application/json;charset=utf-8');
 
my $resp = $ua->request($req);
if ($resp->is_success) {
    my $message = $resp->decoded_content;
    #print "Received reply: $message\n";
    print "中文";
}
else {
    print "HTTP GET error code: ", $resp->code, "\n";
    print "HTTP GET error message: ", $resp->message, "\n";
}