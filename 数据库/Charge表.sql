USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Charge]    Script Date: 07/14/2020 20:32:33 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Charge](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[RunningNumber] [nvarchar](50) NOT NULL,
	[PlateNumber] [nvarchar](50) NULL,
	[PlateType] [nvarchar](50) NULL,
	[ReportNumber] [nvarchar](50) NULL,
	[TotalDetTimes] [int] NULL,
	[EntryTime] [datetime] NULL,
	[EntryOperator] [nvarchar](50) NULL,
	[ChargingTime] [datetime] NULL,
	[AmountOfCharges] [decimal](18, 4) NULL,
	[IsBackOff] [bit] NULL,
	[ChargeingStatus] [nvarchar](50) NULL,
	[TollCollector] [nvarchar](50) NULL,
	[Owner] [nvarchar](50) NULL,
	[VehType] [nvarchar](50) NULL,
	[UnladenMass] [nvarchar](50) NULL,
	[MaximumTotalMass] [nvarchar](50) NULL,
	[DetType] [nvarchar](50) NULL,
	[OperationalOfReason] [nvarchar](50) NULL,
	[ChargeItem] [nvarchar](50) NULL,
	[IsArrears] [nvarchar](50) NULL,
	[UnitName] [nvarchar](200) NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,	
 CONSTRAINT [PK_CHARGE] PRIMARY KEY CLUSTERED 
(
	[RunningNumber] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


