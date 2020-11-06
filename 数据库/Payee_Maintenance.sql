USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Payee_Maintenance]    Script Date: 11/05/2020 15:18:03 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Payee_Maintenance](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[Unit_Name] [nvarchar](50) NOT NULL,
	[Unit_Code] [nvarchar](50) NULL,
	[Taxpayer_Identification_Number] [nvarchar](50) NULL,
	[Unit_Address] [nvarchar](50) NULL,
	[Unit_Phone] [nvarchar](50) NULL,
	[Amount_Of_Arrears] [decimal](18, 4) NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_Payee_Maintenance] PRIMARY KEY CLUSTERED 
(
	[Unit_Name] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


