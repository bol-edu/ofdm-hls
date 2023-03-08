`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 02/25/2020 01:13:15 PM
// Design Name: 
// Module Name: inverter
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module QAM #(parameter DATA_WIDTH=64,
             parameter IN_WL=22,
             parameter IN_IL=7)
   (
    input    axi_clk,
    input    axi_reset_n,
    //AXI4-S slave i/f
    input    s_axis_valid,
    input [DATA_WIDTH-1:0] s_axis_data,
    input s_axis_last,
    output s_axis_ready,
    //AXI4-S master i/f
    output reg  m_axis_valid,
    output reg [DATA_WIDTH-1:0] m_axis_data,
    output reg m_axis_last,
    input    m_axis_ready
    );
    
    reg [DATA_WIDTH-1:0] n_m_axis_data;
    reg cs,ns;
    ////////////////////////////////////////////////////
    reg [1:0] state;
    reg  [DATA_WIDTH-1:0] s_axis_reg;
    reg s_axis_valid_reg;
    
    always @(posedge axi_clk or negedge axi_reset_n) begin   //
        if(~axi_reset_n) begin
            m_axis_data <= 0;
            m_axis_valid <= 0;
            cs <= 0;
            state <= 0;
            s_axis_reg <= 0;
            s_axis_valid_reg <= 0;
            m_axis_last <= 0;
        end
        else begin
            case(state)
                // ?取?入信?
                2'd0: begin
                    if (s_axis_valid) begin
                        s_axis_reg   <= s_axis_data;
                        s_axis_valid_reg <= 1;
                        state        <= 1;
                    end
                end
                // ?算的?果
                2'd1: begin
                    m_axis_data   <= n_m_axis_data;
                    m_axis_valid <= 1;
                    m_axis_last  <= s_axis_last;
                    state        <= 2;
                    cs <= ns;
                end
                // 等待?出信?被消?
                2'd2: begin
                    if (m_axis_ready) begin
                      s_axis_valid_reg <= 0;
                      m_axis_valid <= 0;
                      state        <= 0;
                    end
                end
            endcase
        
        end
    end
    //------------------------------------------combination---------------------------------------//
    assign s_axis_ready = (state == 0);
    always @(*) begin
       if(s_axis_valid_reg) begin
           case(cs)
                1'd0: begin
                    n_m_axis_data = s_axis_reg;
                    if(s_axis_reg[63:48] == 16'hffff) begin
                        ns = 1'd1;
                    end
                    else begin
                        ns = 1'd0;
                    end
                end
                default: begin
                    ns = cs;
                    case(s_axis_reg[1:0])
                        2'd0: begin   //0
                            n_m_axis_data[31:0] = 32'b00000000001111101000000000000000;//-7'd3;
                        end
                        2'd1: begin   //1
                            n_m_axis_data[31:0] = 32'b00000000001111111000000000000000;//-7'd1;
                        end
                        2'd2: begin   //2
                            n_m_axis_data[31:0] = 32'b00000000000000011000000000000000;//7'd3;
                        end
                        default: begin //3
                            n_m_axis_data[31:0] = 32'b00000000000000001000000000000000;//7'd1;
                        end                    
                    endcase
                    case(s_axis_reg[3:2])
                        2'd0: begin   //0
                            n_m_axis_data[63:32] = 32'b00000000001111101000000000000000;//-7'd3;
                        end
                        2'd1: begin   //1
                            n_m_axis_data[63:32] = 32'b00000000001111111000000000000000;//-7'd1;
                        end
                        2'd2: begin   //2
                            n_m_axis_data[63:32] = 32'b00000000000000011000000000000000;//7'd3;
                        end
                        default: begin //3
                            n_m_axis_data[63:32] = 32'b00000000000000001000000000000000;//7'd1;
                        end                    
                    endcase
                    //n_m_axis_data = s_axis_reg + 1;
                end
            endcase
       end
       else begin
            n_m_axis_data = m_axis_data;
            ns = cs;
       end
    end
    
endmodule