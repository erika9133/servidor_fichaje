--
-- PostgreSQL database dump
--

-- Dumped from database version 11.2
-- Dumped by pg_dump version 11.2

-- Started on 2019-03-12 18:29:45 CET

SET statement_timeout = 0;
SET lock_timeout = 0;
SET idle_in_transaction_session_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = on;
SELECT pg_catalog.set_config('search_path', '', false);
SET check_function_bodies = false;
SET client_min_messages = warning;
SET row_security = off;

SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 197 (class 1259 OID 16393)
-- Name: clientes; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.clientes (
    clientes_uuid uuid NOT NULL,
    clientes_pass character varying NOT NULL,
    clientes_user character varying NOT NULL,
    clientes_admin boolean DEFAULT false NOT NULL
);


ALTER TABLE public.clientes OWNER TO postgres;

--
-- TOC entry 198 (class 1259 OID 16402)
-- Name: log; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.log (
    log_uuid uuid NOT NULL,
    usuarios_uuid uuid NOT NULL,
    log_type character varying(3) NOT NULL,
    log_date timestamp(0) without time zone DEFAULT now() NOT NULL
);


ALTER TABLE public.log OWNER TO postgres;

--
-- TOC entry 196 (class 1259 OID 16385)
-- Name: usuarios; Type: TABLE; Schema: public; Owner: postgres
--

CREATE TABLE public.usuarios (
    usuarios_uuid uuid NOT NULL,
    usuarios_pass character varying NOT NULL,
    usuarios_ean13 character varying(13),
    usuarios_valido boolean DEFAULT false NOT NULL,
    usuarios_codigo character varying(5) NOT NULL,
    usuarios_name character varying
);


ALTER TABLE public.usuarios OWNER TO postgres;

--
-- TOC entry 2444 (class 0 OID 16393)
-- Dependencies: 197
-- Data for Name: clientes; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.clientes (clientes_uuid, clientes_pass, clientes_user, clientes_admin) FROM stdin;
3abb4ff1-a49d-4c2d-9a10-f3c7b1109fe5	cliente1234	cliente1234	f
b40858ba-3acf-4c2d-97e1-af2755306cd7	admin	admin	t
\.


--
-- TOC entry 2445 (class 0 OID 16402)
-- Dependencies: 198
-- Data for Name: log; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.log (log_uuid, usuarios_uuid, log_type, log_date) FROM stdin;
0d5ac08d-2d1b-430f-a42f-e096d440c9d7	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-11 15:10:06
dbacbce8-4aa4-4348-8fb5-c2a7855bba54	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-11 15:13:13
722c52e4-154d-476f-bbe8-411fc64c0907	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:23
16f50303-9648-498e-b61d-5002b62cc37a	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:34
5fe2df74-a94a-4ae8-83e6-bb1fce513358	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:39
1ccf901f-fbbb-4698-9dd9-7b0aad7219fe	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:39
ef0f9311-3dd0-480d-bd40-3519265d09a3	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:39
0d54254f-e9ab-4b0c-a8ed-676639517fcd	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 08:58:47
c0c06cf9-96ba-4f51-9cf9-62d8d733525d	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 09:05:01
fae45751-41d6-41dd-aeb3-c9ddbf640318	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 09:05:08
78b5994d-1bec-447d-aca7-debc744cf073	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 09:09:51
2c4b9124-a962-4bb5-a76b-16bbefa01206	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 09:13:07
16bda22f-f1b3-40b4-a0d9-323c5565d5f3	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 09:14:01
8dec84dc-b7da-4d71-8148-8992a5f34a96	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 11:07:04
ec26fec6-0fa1-421d-9029-167d63e40dac	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 11:19:53
e0ce3da0-e8a5-4f47-93ac-87c61317d71a	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 11:53:07
bfb208ec-e76e-4ede-ba48-1ad50c45af4a	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 12:02:53
e40b6f1e-26e8-42e0-b8a3-782e5501df7d	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 12:07:05
5969b28d-a995-4ac1-8733-307032c65daf	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	out	2019-03-12 12:08:32
31e7f4f6-36e9-465e-bb02-482075ef2cb2	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 12:10:26
c9a722a2-b38c-4e03-bed5-2c395f9d2857	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	out	2019-03-12 12:11:13
755f8000-358b-4672-b4f2-bbebb9fee166	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	out	2019-03-12 12:11:32
51636c28-beed-46aa-a355-73ad225ba833	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	out	2019-03-12 12:18:10
7077e480-7590-457a-a429-4d033ed7ab72	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 17:07:09
e62d7019-21ab-49f9-ac01-e05f5645a738	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 17:10:22
b0aca26b-1254-4a24-8b31-63ff8a87173e	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 17:10:31
9a7bcab8-a5d3-4090-b5bc-3395daea8b45	4a000605-bc8a-4ceb-96da-cdc5a9d829f3	in	2019-03-12 17:11:37
\.


--
-- TOC entry 2443 (class 0 OID 16385)
-- Dependencies: 196
-- Data for Name: usuarios; Type: TABLE DATA; Schema: public; Owner: postgres
--

COPY public.usuarios (usuarios_uuid, usuarios_pass, usuarios_ean13, usuarios_valido, usuarios_codigo, usuarios_name) FROM stdin;
4a000605-bc8a-4ceb-96da-cdc5a9d829f3	1234	8411111000001	t	00000	pepe
a100a4d8-9226-4d17-a09f-3e3a77bf584c	pepe2	841111100018	t	00001	1234
63438a18-0ef2-4eed-bc9a-69aed4843feb	pepe2	841111100027	t	00002	1234
32e64a28-fba2-44df-9b67-7115df7be346	pep22	841111100036	t	00003	1234
23f0f88b-8483-42ae-a854-a88e0fc29d86	pepe2	8411111000054	t	00005	1234
60e4efb3-9a4c-48a5-a811-f8e064d1a913	pepe2	841111100045	t	00004	1234
\.


--
-- TOC entry 2318 (class 2606 OID 16400)
-- Name: clientes clientes_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.clientes
    ADD CONSTRAINT clientes_pkey PRIMARY KEY (clientes_uuid);


--
-- TOC entry 2320 (class 2606 OID 16407)
-- Name: log log_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.log
    ADD CONSTRAINT log_pkey PRIMARY KEY (log_uuid);


--
-- TOC entry 2316 (class 2606 OID 16389)
-- Name: usuarios usuarios_pkey; Type: CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.usuarios
    ADD CONSTRAINT usuarios_pkey PRIMARY KEY (usuarios_uuid);


--
-- TOC entry 2321 (class 2606 OID 16408)
-- Name: log log_fk1; Type: FK CONSTRAINT; Schema: public; Owner: postgres
--

ALTER TABLE ONLY public.log
    ADD CONSTRAINT log_fk1 FOREIGN KEY (usuarios_uuid) REFERENCES public.usuarios(usuarios_uuid) ON UPDATE SET NULL ON DELETE SET NULL;


-- Completed on 2019-03-12 18:29:45 CET

--
-- PostgreSQL database dump complete
--

