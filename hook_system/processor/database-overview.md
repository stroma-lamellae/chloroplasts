                     List of relations
 Schema |             Name             |   Type   |  Owner
--------+------------------------------+----------+---------
 public | accounts                     | table    | stromae
 public | institutions                 | table    | stromae
 public | institutions_id_increase_seq | sequence | stromae
 public | jobs


                                            Table "public.institutions"
       Column        |          Type          |                             Modifiers
---------------------+------------------------+--------------------------------------------------------------------
 licence_number      | character varying(50)  | not null
 institution_name    | character varying(50)  |
 institution_address | character varying(100) |
 institution_id      | integer                | not null default nextval('institutions_id_increase_seq'::regclass)
 contact_name        | character varying(50)  | not null
 contact_email       | character varying(50)  | not null
Indexes:
    "institutions_pkey" PRIMARY KEY, btree (licence_number)
    "institutions_institution_name_key" UNIQUE CONSTRAINT, btree (institution_name)
Referenced by:
    TABLE "accounts" CONSTRAINT "accounts_licence_number_fkey" FOREIGN KEY (licence_number) REFERENCES institutions(licence_number) ON DELETE CASCADE



              Table "public.accounts"
     Column     |         Type          | Modifiers
----------------+-----------------------+-----------
 user_id        | character varying(50) |
 user_email     | character varying(50) | not null
 licence_number | character varying(50) | not null
 user_name      | character varying(50) | not null
Indexes:
    "accounts_pkey" PRIMARY KEY, btree (user_email, licence_number)
    "accounts_user_email_key" UNIQUE CONSTRAINT, btree (user_email)
    "accounts_user_id_key" UNIQUE CONSTRAINT, btree (user_id)
Foreign-key constraints:
    "accounts_licence_number_fkey" FOREIGN KEY (licence_number) REFERENCES institutions(licence_number) ON DELETE CASCADE
Referenced by:
    TABLE "jobs" CONSTRAINT "jobs_user_email_fkey" FOREIGN KEY (user_email) REFERENCES accounts(user_email) ON DELETE CASCADE



              Table "public.jobs"
   Column   |         Type          | Modifiers
------------+-----------------------+-----------
 job_id     | integer               | not null
 user_email | character varying(50) | not null
Indexes:
    "jobs_pkey" PRIMARY KEY, btree (job_id, user_email)
    "jobs_job_id_key" UNIQUE CONSTRAINT, btree (job_id)
Foreign-key constraints:
    "jobs_user_email_fkey" FOREIGN KEY (user_email) REFERENCES accounts(user_email) ON DELETE CASCADE


