---
title: setup-pgtap-and-pg-prove
---

Pgtap And Pg Prove

# Setup Pgtap and PgProve

pg_prove can be found on the cpan website. If it can\'t be found,
here\'s the source.

```{.perl .numberLines}
#!/usr/bin/perl -w

use strict;
use App::Prove;
use Getopt::Long;

our $VERSION = '3.35';
$|++;

# Fire up the app, process args, and run the tests.
my $app = App::Prove::pgTAP->new;
$app->process_args(@ARGV);
exit($app->run ? 0 : 1);

#######################################################################################
package App::Prove::pgTAP;
use base 'App::Prove';

BEGIN {
    __PACKAGE__->mk_methods(qw(
        psql dbname username host port pset set runtests schema match ext
    ));
}

sub _initialize {
    my $self = shift->SUPER::_initialize(@_);

    # Set up defaults.
    $self->{sources} = ['pgTAP'];
    $self->{color} = 1;
    $self->{comments} = 1;
    return $self;
}

sub process_args {
    my $self = shift;
    my $opts;
    # We need to locally define a function to do argument processing.
    my $get_options = sub(@) {
        Getopt::Long::Configure(qw(no_ignore_case bundling pass_through));
        # Silence "Duplicate specification" warnings, since we replace some of
        # App::Prove's options.
        local $^W;
        return Getopt::Long::GetOptions(
            @_,
            'psql-bin|b=s' => \$opts->{psql},
            'dbname|d=s'   => \$opts->{dbname},
            'username|U=s' => \$opts->{username},
            'host|h=s'     => \$opts->{host},
            'port|p=s'     => \$opts->{port},
            'pset|P=s%'    => \$opts->{pset},
            'set|S=s%'     => \$opts->{set},
            'runtests|R'   => \$self->{runtests},
            'schema|s=s'   => \$self->{schema},
            'match|x=s'    => \$self->{match},
            'version|V'    => \$self->{show_version},
            'help|H|?'     => \$self->{show_help},
            'man|m'        => \$self->{show_man},
        );
    };

    do {
        # Replace GetOptions in App::Prove and process the args. Yes, this is
        # ugly, but it's the only way to inject additional options into the
        # processing without running GetOptions twice (which has its own
        # issues; see https://rt.cpan.org/Ticket/Display.html?id=114335).
        no warnings 'redefine';
        local *App::Prove::GetOptions = $get_options;
        $self->SUPER::process_args(@_);
    };

    # Set argv to pass stuff through to pgTAP.
    push @{ $self->{argv} } => (
        (map { ('--pgtap-option' =>  } @{ $self->{extensions} || [] }),
        (map {
            ('--pgtap-option' =>
        } grep {
            $opts->{$_}
        } qw(psql dbname username host port)),
        (map {
            ('--pgtap-option' =>
        } keys %{ $opts->{pset} }),
        (map {
            ('--pgtap-option' =>
        } keys %{ $opts->{set} })
    );

    $self->{extensions} ||= ['.pg'];
    return;
}

sub _get_tests {
    my $self = shift;

    # --schema and --match assume --runtests.
    return $self->SUPER::_get_tests(@_)
        unless $self->{runtests} || $self->{schema} || $self->{match};

    # We're just going to call 'runtests()'.
    my @args;
    for my $key (qw(schema match)) {
        next unless $self->{$key};
        (my $arg = $self->{$key}) =~ s/'/\\'/g;
        # Gotta cast the arguments.
        push @args, "'$arg'::" . ($key eq 'schema' ? 'name' : 'text');
    }

    my $runtests_call = 'runtests(' . join( ', ', @args ) . ');';
    return [
        "pgsql: SELECT * FROM $runtests_call",
        $runtests_call,
    ];
}

sub print_version {
    my $self = shift;
    print 'pg_prove ', main->VERSION, $/;
}

sub _help {
    my ( $self, $verbosity ) = @_;
    require Pod::Usage;
    Pod::Usage::pod2usage(
        '-sections' => $verbosity > 1 ? '.+' : '(?i:(Usage|Options))',
        '-verbose'  => 99,
        '-exitval'  => 0,
    )
}

__END__
```

Pgtap can be cloned from source at: https://github.com/theory/pgtap

clone it down, and run `make && make install && make installcheck`.

move over the files in sql/\* to the extensions directory: as well, move
over the control file to the extensions directory.

/Applications/Postgres.app/Contents/Versions/12/share/postgresql/extension/

and run `psql -c CREATE EXTENSION pgtap;` to create the pg_tap
extension.

you can check if pgtap has been installed by running this script:

```sh
pg_prove -U postgres ${path-to-tests}
```

```sql
-- Start transaction and plan the tests.
BEGIN;
SELECT plan(1);

-- Run the tests.
SELECT pass( 'My test passed, w00t!' );

-- Finish the tests and clean up.
SELECT * FROM finish();
ROLLBACK;
```
