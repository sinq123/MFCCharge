USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Fee_Items]    Script Date: 07/14/2020 20:35:47 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Fee_Items](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[TypeOfCharge] [nvarchar](50) NOT NULL,
	[AmountOfCharges] [nvarchar](50) NULL,
	[DetType] [nvarchar](50) NULL,
	[DetTypeCode] [nvarchar](50) NULL,
	[Remark] [nvarchar](1024) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL,
 CONSTRAINT [PK_FEE_ITEMS] PRIMARY KEY CLUSTERED 
(
	[AutoID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]

GO


