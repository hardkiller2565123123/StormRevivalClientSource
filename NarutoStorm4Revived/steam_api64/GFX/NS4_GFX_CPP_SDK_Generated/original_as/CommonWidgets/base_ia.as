package script.duel_boss
{
   import flash.display.MovieClip;
   import flash.events.Event;
   
   public class base_ia extends MovieClip
   {
      
      public const CCD_IA_BTN_R_RIGHT:String = "btn_1";
      
      public const CCD_IA_BTN_R_DOWN:String = "btn_2";
      
      public const CCD_IA_BTN_R_LEFT:String = "btn_3";
      
      public const CCD_IA_BTN_R_UP:String = "btn_4";
      
      public const CCD_IA_BTN_L_1:String = "btn_l1";
      
      public const CCD_IA_BTN_L_2:String = "btn_l2";
      
      public const CCD_IA_BTN_R_1:String = "btn_r1";
      
      public const CCD_IA_BTN_R_2:String = "btn_r2";
      
      public const CCD_IA_BTN_KEY_UP:String = "key_up";
      
      public const CCD_IA_BTN_KEY_RIGHT:String = "key_r";
      
      public const CCD_IA_BTN_KEY_DOWN:String = "key_dwn";
      
      public const CCD_IA_BTN_KEY_LEFT:String = "key_l";
      
      public const CCD_IA_BTN_R_STICK_LOOP:String = "stk_r";
      
      public const CCD_IA_BTN_L_STICK_LOOP:String = "stk_l";
      
      public const CCD_IA_BTN_R_STICK_RIGHT:String = "stk_r_r";
      
      public const CCD_IA_BTN_R_STICK_DOWN:String = "stk_r_dwn";
      
      public const CCD_IA_BTN_R_STICK_LEFT:String = "stk_r_l";
      
      public const CCD_IA_BTN_R_STICK_UP:String = "stk_r_up";
      
      public const CCD_IA_BTN_L_STICK_RIGHT:String = "stk_l_r";
      
      public const CCD_IA_BTN_L_STICK_DOWN:String = "stk_l_dwn";
      
      public const CCD_IA_BTN_L_STICK_LEFT:String = "stk_l_l";
      
      public const CCD_IA_BTN_L_STICK_UP:String = "stk_l_up";
      
      public const CCD_HLD_BTN_R_RIGHT:String = "btn_1_hld";
      
      public const CCD_HLD_BTN_R_DOWN:String = "btn_2_hld";
      
      public const CCD_HLD_BTN_R_LEFT:String = "btn_3_hld";
      
      public const CCD_HLD_BTN_R_UP:String = "btn_4_hld";
      
      public const CCD_HLD_BTN_L_1:String = "btn_l1_hld";
      
      public const CCD_HLD_BTN_L_2:String = "btn_l2_hld";
      
      public const CCD_HLD_BTN_R_1:String = "btn_r1_hld";
      
      public const CCD_HLD_BTN_R_2:String = "btn_r2_hld";
      
      public const CCD_HLD_BTN_KEY_UP:String = "key_up";
      
      public const CCD_HLD_BTN_KEY_RIGHT:String = "key_r";
      
      public const CCD_HLD_BTN_KEY_DOWN:String = "key_dwn";
      
      public const CCD_HLD_BTN_KEY_LEFT:String = "key_l";
      
      public const CCD_HLD_BTN_R_STICK_LOOP:String = "stk_roll_r";
      
      public const CCD_HLD_BTN_L_STICK_LOOP:String = "stk_roll_l";
      
      public const CCD_HLD_BTN_R_STICK_RIGHT:String = "stk_r_r";
      
      public const CCD_HLD_BTN_R_STICK_DOWN:String = "stk_r_dwn";
      
      public const CCD_HLD_BTN_R_STICK_LEFT:String = "stk_r_l";
      
      public const CCD_HLD_BTN_R_STICK_UP:String = "stk_r_up";
      
      public const CCD_HLD_BTN_L_STICK_RIGHT:String = "stk_l_r";
      
      public const CCD_HLD_BTN_L_STICK_DOWN:String = "stk_l_dwn";
      
      public const CCD_HLD_BTN_L_STICK_LEFT:String = "stk_l_l";
      
      public const CCD_HLD_BTN_L_STICK_UP:String = "stk_l_up";
      
      public const CCD_FAIL_BTN_R_RIGHT:String = "btn_1d";
      
      public const CCD_FAIL_BTN_R_DOWN:String = "btn_2d";
      
      public const CCD_FAIL_BTN_R_LEFT:String = "btn_3d";
      
      public const CCD_FAIL_BTN_R_UP:String = "btn_4d";
      
      public const CCD_FAIL_BTN_L_1:String = "btn_l1d";
      
      public const CCD_FAIL_BTN_L_2:String = "btn_l2d";
      
      public const CCD_FAIL_BTN_R_1:String = "btn_r1d";
      
      public const CCD_FAIL_BTN_R_2:String = "btn_r2d";
      
      public const CCD_FAIL_BTN_KEY_UP:String = "key_d";
      
      public const CCD_FAIL_BTN_KEY_RIGHT:String = "key_d";
      
      public const CCD_FAIL_BTN_KEY_DOWN:String = "key_d";
      
      public const CCD_FAIL_BTN_KEY_LEFT:String = "key_d";
      
      public const CCD_FAIL_BTN_R_STICK_LOOP:String = "stk_d";
      
      public const CCD_FAIL_BTN_L_STICK_LOOP:String = "stk_d";
      
      public const CCD_FAIL_BTN_R_STICK_RIGHT:String = "stk_d";
      
      public const CCD_FAIL_BTN_R_STICK_DOWN:String = "stk_d";
      
      public const CCD_FAIL_BTN_R_STICK_LEFT:String = "stk_d";
      
      public const CCD_FAIL_BTN_R_STICK_UP:String = "stk_d";
      
      public const CCD_FAIL_BTN_L_STICK_RIGHT:String = "stk_d";
      
      public const CCD_FAIL_BTN_L_STICK_DOWN:String = "stk_d";
      
      public const CCD_FAIL_BTN_L_STICK_LEFT:String = "stk_d";
      
      public const CCD_FAIL_BTN_L_STICK_UP:String = "stk_d";
      
      public const CCD_IA_EFF_NORMAL:uint = 0;
      
      public const CCD_IA_EFF_SPECIAL:uint = 1;
      
      protected var m_iaBtnTbl:Array = new Array();
      
      protected var m_hldBtnTbl:Array = new Array();
      
      protected var m_failBtnTbl:Array = new Array();
      
      protected var m_btnNo:int;
      
      protected var m_gaugeParam:IaGaugeParam = new IaGaugeParam();
      
      public var SuccessIa:Function;
      
      public var FailedIa:Function;
      
      public var GreatSuccessIa:Function;
      
      public var SetEnableInput:Function;
      
      public var PlaySuccessSE:Function;
      
      public function base_ia()
      {
         super();
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_RIGHT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_DOWN);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_LEFT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_UP);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_1);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_2);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_1);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_2);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_KEY_UP);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_KEY_RIGHT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_KEY_DOWN);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_KEY_LEFT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_STICK_LOOP);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_STICK_LOOP);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_STICK_RIGHT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_STICK_DOWN);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_STICK_LEFT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_R_STICK_UP);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_STICK_RIGHT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_STICK_DOWN);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_STICK_LEFT);
         this.m_iaBtnTbl.push(this.CCD_IA_BTN_L_STICK_UP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_RIGHT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_DOWN);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_LEFT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_UP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_1);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_2);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_1);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_2);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_KEY_UP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_KEY_RIGHT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_KEY_DOWN);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_KEY_LEFT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_STICK_LOOP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_STICK_LOOP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_STICK_RIGHT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_STICK_DOWN);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_STICK_LEFT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_R_STICK_UP);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_STICK_RIGHT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_STICK_DOWN);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_STICK_LEFT);
         this.m_hldBtnTbl.push(this.CCD_HLD_BTN_L_STICK_UP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_RIGHT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_DOWN);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_LEFT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_UP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_1);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_2);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_1);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_2);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_KEY_UP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_KEY_RIGHT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_KEY_DOWN);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_KEY_LEFT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_STICK_LOOP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_STICK_LOOP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_STICK_RIGHT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_STICK_DOWN);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_STICK_LEFT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_R_STICK_UP);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_STICK_RIGHT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_STICK_DOWN);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_STICK_LEFT);
         this.m_failBtnTbl.push(this.CCD_FAIL_BTN_L_STICK_UP);
         if(this.m_iaBtnTbl.length != this.m_hldBtnTbl.length || this.m_iaBtnTbl.length != this.m_failBtnTbl.length)
         {
            trace("script.duel_boss.base_ia ButtonTbl Error!!!!");
         }
      }
      
      public function Initialize(param1:uint, param2:uint, param3:int, param4:uint, param5:Boolean, param6:Boolean, param7:uint) : *
      {
      }
      
      public function Update(param1:Event) : *
      {
      }
      
      public function SetGaugeParam(param1:int, param2:uint, param3:uint, param4:Number, param5:Number, param6:Number, param7:Number, param8:Boolean) : *
      {
         this.m_gaugeParam.m_intervalFrame = param1;
         this.m_gaugeParam.m_nowTime = param2;
         this.m_gaugeParam.m_nowGauge = param3;
         this.m_gaugeParam.m_posX = param4;
         this.m_gaugeParam.m_posY = param5;
         this.m_gaugeParam.m_scaleX = param6;
         this.m_gaugeParam.m_scaleY = param7;
         if(param8)
         {
            this.m_gaugeParam.m_isInput = param8;
         }
      }
      
      public function ReplayAnim() : *
      {
      }
      
      public function StopAnim() : *
      {
         this.RemoveUpdate();
         this.stop();
      }
      
      public function PlayAnim() : *
      {
         if(hasEventListener(Event.ENTER_FRAME) == false)
         {
            addEventListener(Event.ENTER_FRAME,this.Update);
         }
         this.play();
      }
      
      public function SetTimeVisible(param1:Boolean) : *
      {
      }
      
      public function SetBtnGaugeVisible(param1:Boolean) : *
      {
      }
      
      public function SetIaCommandVisible(param1:Boolean) : *
      {
         this.visible = param1;
         if(param1 == false)
         {
            this.stop();
         }
      }
      
      protected function RemoveUpdate() : *
      {
         if(hasEventListener(Event.ENTER_FRAME) == true)
         {
            removeEventListener(Event.ENTER_FRAME,this.Update);
         }
      }
   }
}

