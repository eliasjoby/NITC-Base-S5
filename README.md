# NITCbase

Repo contains the project files of NITCbase, a Relational Database Management System (RDBMS) built from scratch as a part of the DBMS Lab Course I took in Sem 5 at NITC.

## Foreword

This repository chronicles all stages of building NITCbase, turning an empty disk interface into a functioning 8-layer RDBMS.

## Table of Contents

* [Overview](#overview)
  + [Preparatory Stages](#preparatory-stages)
  + [Storage and Access Stages](#storage-and-access-stages)
  + [Query and Indexing Stages](#query-and-indexing-stages)
  + [Additions](#additions)
* [Hazards](#hazards)
* [Useful Resources](#useful-resources)
* [Done by](#done-by)
* [Fork of](#fork-of)

## Overview

### Preparatory stages

* Stage 0 - [Installation and Preparation](https://nitcbase.github.io/docs/Roadmap/Stage00)
* Stage 1 - [Understanding the Disk Interface](https://nitcbase.github.io/docs/Roadmap/Stage01)
* Stage 2 - [Record Blocks and Catalogs](https://nitcbase.github.io/docs/Roadmap/Stage02)
* Stage 3 - [The Disk Buffer and Catalog Caches](https://nitcbase.github.io/docs/Roadmap/Stage03)

### Storage and access stages

* Stage 4 - [Linear Search on Relations](https://nitcbase.github.io/docs/Roadmap/Stage04)
* Stage 5 - [Opening Relations](https://nitcbase.github.io/docs/Roadmap/Stage05)
* Stage 6 - [Buffer Management and Disk Write-back](https://nitcbase.github.io/docs/Roadmap/Stage06)
* Stage 7 - [Inserting Records Into Relations](https://nitcbase.github.io/docs/Roadmap/Stage07)
* Stage 8 - [Creating and Deleting Relations](https://nitcbase.github.io/docs/Roadmap/Stage08)

### Query and indexing stages

* Stage 9 - [Selection and Projection on Relations](https://nitcbase.github.io/docs/Roadmap/Stage09)
* Stage 10 - [B+ Tree Search on Relations](https://nitcbase.github.io/docs/Roadmap/Stage10)
* Stage 11 - [Index Creation and Deletion](https://nitcbase.github.io/docs/Roadmap/Stage11)
* Stage 12 - [Join on Relations](https://nitcbase.github.io/docs/Roadmap/Stage12)

### Additions

* compile_script.sh - Script which when placed in the mynitcbase directory and run will compile every source file. Updating the file path is necessary.
* Sample schema/CSV files used for testing each stage's functionality.

## Hazards

* Some earlier stages may not work as intended if run in the commit of a further stage. For best results, checkout stage completion commit of the stage to be run.
* Always exit NITCbase before running commands through the XFS Interface, and vice versa, to avoid disk/cache desynchronization.

## Useful resources

* Documentation - [NITCbase](https://nitcbase.github.io/)

## Done by

* Portfolio - [Elias Joby](https://www.linkedin.com/in/elias-joby)

## Fork of

* NITCbase - [nitcbase](https://github.com/nitcbase)
