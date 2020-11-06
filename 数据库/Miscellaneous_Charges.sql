USE [NHMFDServerDB]
GO

/****** Object:  Table [dbo].[Miscellaneous_Charges]    Script Date: 07/24/2020 09:45:06 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

CREATE TABLE [dbo].[Miscellaneous_Charges](
	[AutoID] [int] IDENTITY(1,1) NOT NULL,
	[TypeOfCharge] [nvarchar](50) NULL,
	[AmountOfCharges] [decimal](18, 4) NULL,
	[Remark] [nvarchar](max) NULL,
	[Reserved1] [nvarchar](50) NULL,
	[Reserved2] [nvarchar](50) NULL,
	[Reserved3] [nvarchar](50) NULL
 CONSTRAINT [PK_MISCELLANEOUS_CHARGE] PRIMARY KEY CLUSTERED 
(
	[AutoID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY] TEXTIMAGE_ON [PRIMARY]

GO


