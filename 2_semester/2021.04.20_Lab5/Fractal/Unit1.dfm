object Form1: TForm1
  Left = 0
  Top = 0
  AutoSize = True
  BorderStyle = bsSingle
  Caption = 'Fractal FROM NIKITOS'
  ClientHeight = 600
  ClientWidth = 800
  Color = clBtnText
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 800
    Height = 600
    Cursor = crCross
    OnMouseMove = Image1MouseMove
  end
end
