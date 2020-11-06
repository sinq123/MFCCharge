use [NHMFDServerDB]
go

alter table Charge add IsArrears nvarchar(50)
alter table Charge add UnitName nvarchar(200)