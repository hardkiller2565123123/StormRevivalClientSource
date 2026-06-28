package InputPad
{
   import flash.external.ExternalInterface;
   
   public class InputPadKeyCode
   {
      
      public var CCD_PAD_1P:uint = 0;
      
      public var CCD_PAD_2P:uint = 1;
      
      private var CCD_GET_INPUT_BTN_SELECT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_START:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L_UP:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L_DOWN:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L_LEFT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L_RIGHT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R_UP:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R_DOWN:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R_LEFT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R_RIGHT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L1:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L2:uint = 0;
      
      private var CCD_GET_INPUT_BTN_L3:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R1:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R2:uint = 0;
      
      private var CCD_GET_INPUT_BTN_R3:uint = 0;
      
      private var CCD_GET_INPUT_BTN_LS_UP:uint = 0;
      
      private var CCD_GET_INPUT_BTN_LS_DOWN:uint = 0;
      
      private var CCD_GET_INPUT_BTN_LS_LEFT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_LS_RIGHT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_RS_UP:uint = 0;
      
      private var CCD_GET_INPUT_BTN_RS_DOWN:uint = 0;
      
      private var CCD_GET_INPUT_BTN_RS_LEFT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_RS_RIGHT:uint = 0;
      
      private var CCD_GET_INPUT_BTN_OK:uint = 0;
      
      private var CCD_GET_INPUT_BTN_CANCEL:uint = 0;
      
      private var m_isEnable:Boolean = true;
      
      public function InputPadKeyCode()
      {
         super();
         var _loc1_:Boolean = false;
         _loc1_ = true;
         this.CCD_GET_INPUT_BTN_SELECT = uint(ExternalInterface.call("GetKeyInputBtn_Select"));
         this.CCD_GET_INPUT_BTN_START = uint(ExternalInterface.call("GetKeyInputBtn_Start"));
         this.CCD_GET_INPUT_BTN_L_UP = uint(ExternalInterface.call("GetKeyInputBtn_L_Up"));
         this.CCD_GET_INPUT_BTN_L_DOWN = uint(ExternalInterface.call("GetKeyInputBtn_L_Down"));
         this.CCD_GET_INPUT_BTN_L_LEFT = uint(ExternalInterface.call("GetKeyInputBtn_L_Left"));
         this.CCD_GET_INPUT_BTN_L_RIGHT = uint(ExternalInterface.call("GetKeyInputBtn_L_Right"));
         this.CCD_GET_INPUT_BTN_R_UP = uint(ExternalInterface.call("GetKeyInputBtn_R_Up"));
         this.CCD_GET_INPUT_BTN_R_DOWN = uint(ExternalInterface.call("GetKeyInputBtn_R_Down"));
         this.CCD_GET_INPUT_BTN_R_LEFT = uint(ExternalInterface.call("GetKeyInputBtn_R_Left"));
         this.CCD_GET_INPUT_BTN_R_RIGHT = uint(ExternalInterface.call("GetKeyInputBtn_R_Right"));
         this.CCD_GET_INPUT_BTN_L1 = uint(ExternalInterface.call("GetKeyInputBtn_L1"));
         this.CCD_GET_INPUT_BTN_L2 = uint(ExternalInterface.call("GetKeyInputBtn_L2"));
         this.CCD_GET_INPUT_BTN_L3 = uint(ExternalInterface.call("GetKeyInputBtn_L3"));
         this.CCD_GET_INPUT_BTN_R1 = uint(ExternalInterface.call("GetKeyInputBtn_R1"));
         this.CCD_GET_INPUT_BTN_R2 = uint(ExternalInterface.call("GetKeyInputBtn_R2"));
         this.CCD_GET_INPUT_BTN_R3 = uint(ExternalInterface.call("GetKeyInputBtn_R3"));
         this.CCD_GET_INPUT_BTN_LS_UP = uint(ExternalInterface.call("GetKeyInputBtn_LS_Up"));
         this.CCD_GET_INPUT_BTN_LS_DOWN = uint(ExternalInterface.call("GetKeyInputBtn_LS_Down"));
         this.CCD_GET_INPUT_BTN_LS_LEFT = uint(ExternalInterface.call("GetKeyInputBtn_LS_Left"));
         this.CCD_GET_INPUT_BTN_LS_RIGHT = uint(ExternalInterface.call("GetKeyInputBtn_LS_Right"));
         this.CCD_GET_INPUT_BTN_RS_UP = uint(ExternalInterface.call("GetKeyInputBtn_RS_Up"));
         this.CCD_GET_INPUT_BTN_RS_DOWN = uint(ExternalInterface.call("GetKeyInputBtn_RS_Down"));
         this.CCD_GET_INPUT_BTN_RS_LEFT = uint(ExternalInterface.call("GetKeyInputBtn_RS_Left"));
         this.CCD_GET_INPUT_BTN_RS_RIGHT = uint(ExternalInterface.call("GetKeyInputBtn_RS_Right"));
         this.CCD_GET_INPUT_BTN_OK = uint(ExternalInterface.call("GetKeyInputBtn_Ok"));
         this.CCD_GET_INPUT_BTN_CANCEL = uint(ExternalInterface.call("GetKeyInputBtn_Cancel"));
         this.CCD_PAD_1P = uint(ExternalInterface.call("GetPad_1P"));
         this.CCD_PAD_2P = uint(ExternalInterface.call("GetPad_2P"));
         if(_loc1_ == false)
         {
            ExternalInterface.call("CallAssertFromSwf","[InputPadKeyCode] CONFIG::IN_GAMEが有効になっていません");
         }
      }
      
      public function GetKeyInputBtn_Select() : uint
      {
         return this.CCD_GET_INPUT_BTN_SELECT;
      }
      
      public function GetKeyInputBtn_Start() : uint
      {
         return this.CCD_GET_INPUT_BTN_START;
      }
      
      public function GetKeyInputBtn_L_Up() : uint
      {
         return this.CCD_GET_INPUT_BTN_L_UP;
      }
      
      public function GetKeyInputBtn_L_Down() : uint
      {
         return this.CCD_GET_INPUT_BTN_L_DOWN;
      }
      
      public function GetKeyInputBtn_L_Left() : uint
      {
         return this.CCD_GET_INPUT_BTN_L_LEFT;
      }
      
      public function GetKeyInputBtn_L_Right() : uint
      {
         return this.CCD_GET_INPUT_BTN_L_RIGHT;
      }
      
      public function GetKeyInputBtn_R_Up() : uint
      {
         return this.CCD_GET_INPUT_BTN_R_UP;
      }
      
      public function GetKeyInputBtn_R_Down() : uint
      {
         return this.CCD_GET_INPUT_BTN_R_DOWN;
      }
      
      public function GetKeyInputBtn_R_Left() : uint
      {
         return this.CCD_GET_INPUT_BTN_R_LEFT;
      }
      
      public function GetKeyInputBtn_R_Right() : uint
      {
         return this.CCD_GET_INPUT_BTN_R_RIGHT;
      }
      
      public function GetKeyInputBtn_L1() : uint
      {
         return this.CCD_GET_INPUT_BTN_L1;
      }
      
      public function GetKeyInputBtn_L2() : uint
      {
         return this.CCD_GET_INPUT_BTN_L2;
      }
      
      public function GetKeyInputBtn_L3() : uint
      {
         return this.CCD_GET_INPUT_BTN_L3;
      }
      
      public function GetKeyInputBtn_R1() : uint
      {
         return this.CCD_GET_INPUT_BTN_R1;
      }
      
      public function GetKeyInputBtn_R2() : uint
      {
         return this.CCD_GET_INPUT_BTN_R2;
      }
      
      public function GetKeyInputBtn_R3() : uint
      {
         return this.CCD_GET_INPUT_BTN_R3;
      }
      
      public function GetKeyInputBtn_LS_Up() : uint
      {
         return this.CCD_GET_INPUT_BTN_LS_UP;
      }
      
      public function GetKeyInputBtn_LS_Down() : uint
      {
         return this.CCD_GET_INPUT_BTN_LS_DOWN;
      }
      
      public function GetKeyInputBtn_LS_Left() : uint
      {
         return this.CCD_GET_INPUT_BTN_LS_LEFT;
      }
      
      public function GetKeyInputBtn_LS_Right() : uint
      {
         return this.CCD_GET_INPUT_BTN_LS_RIGHT;
      }
      
      public function GetKeyInputBtn_RS_Up() : uint
      {
         return this.CCD_GET_INPUT_BTN_RS_UP;
      }
      
      public function GetKeyInputBtn_RS_Down() : uint
      {
         return this.CCD_GET_INPUT_BTN_RS_DOWN;
      }
      
      public function GetKeyInputBtn_RS_Left() : uint
      {
         return this.CCD_GET_INPUT_BTN_RS_LEFT;
      }
      
      public function GetKeyInputBtn_RS_Right() : uint
      {
         return this.CCD_GET_INPUT_BTN_RS_RIGHT;
      }
      
      public function GetKeyInputBtn_Ok() : uint
      {
         return this.CCD_GET_INPUT_BTN_OK;
      }
      
      public function GetKeyInputBtn_Cancel() : uint
      {
         return this.CCD_GET_INPUT_BTN_CANCEL;
      }
      
      public function GetPad_1P() : uint
      {
         return this.CCD_PAD_1P;
      }
      
      public function GetPad_2P() : uint
      {
         return this.CCD_PAD_2P;
      }
      
      public function SetEnablePad(param1:uint) : *
      {
         ExternalInterface.call("SetEnablePad",param1);
      }
      
      public function SetDisablePad(param1:uint) : *
      {
         ExternalInterface.call("SetDisablePad",param1);
      }
      
      public function EnableAllPad() : *
      {
         ExternalInterface.call("EnableAllPad");
      }
      
      public function DisableAllPad() : *
      {
         ExternalInterface.call("DisableAllPad");
      }
      
      public function SetEnablePadOnly(param1:uint) : *
      {
         ExternalInterface.call("SetEnablePadOnly",param1);
      }
      
      public function SetEnableLocal(param1:Boolean) : *
      {
         this.m_isEnable = param1;
      }
      
      public function GetPadOn() : uint
      {
         return this.m_isEnable ? uint(ExternalInterface.call("GetPadOn")) : 0;
      }
      
      public function GetPadPress() : uint
      {
         return this.m_isEnable ? uint(ExternalInterface.call("GetPadPress")) : 0;
      }
      
      public function GetPadRepeat() : uint
      {
         return this.m_isEnable ? uint(ExternalInterface.call("GetPadRepeat")) : 0;
      }
      
      public function GetPadRelease() : uint
      {
         return this.m_isEnable ? uint(ExternalInterface.call("GetPadRelease")) : 0;
      }
   }
}

